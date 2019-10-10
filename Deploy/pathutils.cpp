//#
//# Copyright (C) 2018-2019 QuasarApp.
//# Distributed under the lgplv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "pathutils.h"

#include <QFileInfo>

PathUtils::PathUtils()
{

}

QString PathUtils::toFullPath(QString path) {
    path.replace('\\', '/');

    int index = -1;
    do {
        path.replace("//", "/");
    } while ((index = path.indexOf("//")) >= 0);

    if (path.left(1) != '/') {
        path.insert(0, '/');
    }

    if (path.right(1) != '/') {
        path.insert(path.size(), '/');
    }

    return path;
}

QString PathUtils::getRelativeLink(QString from, QString to) {

    bool isFile = QFileInfo(to).isFile();
    from = toFullPath(from);
    to = toFullPath(to);

    int lastGeneralDir = 0;
    int index = 0;

    while (from.size() > index && to.size() > index && from[index] == to[index]) {
        if (from[index] == '/') {
            lastGeneralDir = index;
        }
        index++;
    }

    auto result =  "." + getReleativePath(from.mid(lastGeneralDir)) +
            to.mid(lastGeneralDir + 1);

    if (isFile && result.right(1) == '/')
        result = result.left(result.size() - 1);

    return result;
}

// TODO ignore labels may be mistaken for a path, which will lead to improper eating
bool PathUtils::isPath(const QString &path) {
    return path.contains('/') || path.contains('\\') || path == ".";
}

QString PathUtils::getReleativePath(QString path) {
    path = toFullPath(path);

    int left = path.indexOf('/', 0) + 1;
    int righy = path.indexOf('/', left);

    while (righy > 0) {

        path.replace(left, righy - left, "..");

        left = left + 3;
        righy = path.indexOf('/', left);
    }

    return path;
}

QString PathUtils::stripPath(QString path) {
    path.replace('\\', '/');

    int index = -1;
    do {
        path.replace("//", "/");
    } while ((index = path.indexOf("//")) >= 0);

    if (path.left(1) == '/') {
        path = path.right(path.size() - 1);
    }

    if (path.right(1) == '/') {
        path = path.left(path.size() - 1);
    }

    return path;
}