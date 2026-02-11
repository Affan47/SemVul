computeAppName(const std::string& start) {
    if (start.size() < 2) {
        return start;
    }

    if (start[start.size() - 1] == 'd') {

        char tmp[1024];
        getcwd(tmp, sizeof(tmp));
        std::string drive, base, ext;
        Array<std::string> path;
        parseFilename(tmp, drive, path, base, ext);

        std::string shortName = start.substr(0, start.size() - 1);

        if ((path.size() > 1) && (toLower(path.last()) == toLower(shortName))) {
            return shortName;
        }

        if ((path.size() > 2) && (toLower(path[path.size() - 2]) == toLower(shortName))) {
            return shortName;
        }
    }

    return start;
}
