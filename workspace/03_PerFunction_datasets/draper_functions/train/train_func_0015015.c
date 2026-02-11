efreet_menu_directory_dir_scan(const char *path, const char *relative_path,
                                Eina_Hash *cache)
{
    Efreet_Desktop *desktop;
    char buf2[PATH_MAX];
    Eina_Iterator *it;
    Eina_File_Direct_Info *info;
    char *ext;

    it = eina_file_direct_ls(path);
    if (!it) return 1;

    EINA_ITERATOR_FOREACH(it, info)
    {
        const char *fname;

        fname = info->path + info->name_start;
        if (relative_path)
            snprintf(buf2, sizeof(buf2), "%s/%s", relative_path, fname);
        else
            strcpy(buf2, fname);

        if (ecore_file_is_dir(info->path))
            efreet_menu_directory_dir_scan(info->path, buf2, cache);

        else
        {
            ext = strrchr(fname, '.');
            if (!ext || strcmp(ext, ".directory")) continue;

            desktop = efreet_desktop_get(info->path);
            if (!desktop || desktop->type != EFREET_DESKTOP_TYPE_DIRECTORY)
            {
                efreet_desktop_free(desktop);
                continue;
            }

            eina_hash_del(cache, buf2, NULL);
            eina_hash_add(cache, buf2, desktop);
        }
    }
    eina_iterator_free(it);

    return 1;
}
