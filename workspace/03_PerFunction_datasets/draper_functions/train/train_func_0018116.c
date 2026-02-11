fs_tlist_open(fs_backend *be, fs_rid model, int flags)
{
    fs_tlist *l;

    if (fs_backend_model_dirs(be)) {
        char hash[17];
        sprintf(hash, "%016llx", model);
        hash[16] = '\0';
        char *dirname = g_strdup_printf(FS_TLIST_DIRD, fs_backend_get_kb(be),
                                        fs_backend_get_segment(be), hash[0],
                                        hash[1], hash[2], hash[3]);
        struct stat buf;
        int ret = stat(dirname, &buf);
        if (ret) mkdir(dirname, FS_FILE_MODE + 0100);
        char *filename = g_strdup_printf(FS_TLIST_DIR, fs_backend_get_kb(be),
                                         fs_backend_get_segment(be),
                                         hash[0], hash[1],
                                         hash[2], hash[3], hash+4);
        l = fs_tlist_open_filename(filename, flags);
        g_free(filename);
    } else {
        char *filename = g_strdup_printf(FS_TLIST, fs_backend_get_kb(be),
                                         fs_backend_get_segment(be), model);
        l = fs_tlist_open_filename(filename, flags);
        g_free(filename);
    }

    return l;
}
