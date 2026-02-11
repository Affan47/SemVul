fs_clear(Store *store)
{
    struct dirent *de;
    DIR *d = opendir(store->dir.path);

    if (!d) {
        RAISE(IO_ERROR, "clearing files in %s: <%s>",
              store->dir.path, strerror(errno));
    }

    while ((de = readdir(d)) != NULL) {
        if (de->d_name[0] > '/'
                && !file_is_lock(de->d_name)) {
            char path[MAX_FILE_PATH];
            remove(join_path(path, store->dir.path, de->d_name));
        }
    }
    closedir(d);
}
