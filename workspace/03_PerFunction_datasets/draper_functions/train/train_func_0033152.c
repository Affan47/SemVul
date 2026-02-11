lms_parsers_list(int (*cb)(void *data, const char *path), const void *data)
{
    void *datap = (void *)data;
    char path[PATH_MAX] = PLUGINSDIR;
    int base;
    DIR *d;
    struct dirent *de;

    if (!cb)
        return;

    base = sizeof(PLUGINSDIR) - 1;
    if (base + sizeof("/.so") >= PATH_MAX) {
        fprintf(stderr, "ERROR: path is too long '%s'\n", path);
        return;
    }

    d = opendir(path);
    if (!d) {
        fprintf(stderr, "ERROR: could not open directory %s: %s\n",
                path, strerror(errno));
        return;
    }

    path[base] = '/';
    base++;

    while ((de = readdir(d)) != NULL) {
        int len;

        if (de->d_name[0] == '.')
            continue;

        len = strlen(de->d_name);
        if (len < 3 || memcmp(de->d_name + len - 3, ".so", 3) != 0)
            continue;

        memcpy(path + base, de->d_name, len + 1);
        if (!cb(datap, path))
            break;
    }
    closedir(d);
}
