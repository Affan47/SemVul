file_open(const char *base, const char *suffix, bool writable, bool append)
{
    char *file;
    int flags, fd;

    file = concat(base, ".", suffix, (char *) 0);
    flags = writable ? (O_RDWR | O_CREAT) : O_RDONLY;
    if (append)
        flags |= O_APPEND;
    fd = open(file, flags, ARTFILE_MODE);
    if (fd < 0 && writable && errno == ENOENT) {
        char *p = strrchr(file, '/');

        *p = '\0';
        if (!MakeDirectory(file, true)) {
            syswarn("tradindexed: cannot create directory %s", file);
            free(file);
            return -1;
        }
        *p = '/';
        fd = open(file, flags, ARTFILE_MODE);
    }
    if (fd < 0) {
        if (errno != ENOENT)
            syswarn("tradindexed: cannot open %s", file);
        free(file);
        return -1;
    }
    free(file);
    return fd;
}
