fs_each(Store *store, void (*func)(const char *fname, void *arg), void *arg)
{
    struct dirent *de;
    DIR *d = opendir(store->dir.path);

    if (!d) {
        RAISE(IO_ERROR, "doing 'each' in %s: <%s>",
              store->dir.path, strerror(errno));
    }

    while ((de = readdir(d)) != NULL) {
        if (de->d_name[0] > '/'
                && !file_is_lock(de->d_name)) {
            func(de->d_name, arg);
        }
    }
    closedir(d);
}
