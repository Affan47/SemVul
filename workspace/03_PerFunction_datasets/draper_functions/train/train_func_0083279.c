qfile_check_path(const char *path) {
    if (path == NULL)
        return false;

    int nLen = strlen(path);
    if (nLen == 0 || nLen >= PATH_MAX)
        return false;
    else if (strpbrk(path, "\\:*?\"<>|") != NULL)
        return false;
    return true;
}
