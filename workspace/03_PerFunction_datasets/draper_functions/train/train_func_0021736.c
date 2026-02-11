fm_folder_config_open(FmPath *path)
{
    FmFolderConfig *fc = g_slice_new(FmFolderConfig);
    FmPath *sub_path;

    fc->changed = FALSE;

    sub_path = fm_path_new_child(path, ".directory");
    fc->filepath = fm_path_to_str(sub_path);
    fm_path_unref(sub_path);
    if (g_file_test(fc->filepath, G_FILE_TEST_EXISTS))
    {
        fc->kf = g_key_file_new();
        if (g_key_file_load_from_file(fc->kf, fc->filepath,
                                      G_KEY_FILE_KEEP_COMMENTS | G_KEY_FILE_KEEP_TRANSLATIONS,
                                      NULL) &&
            g_key_file_has_group(fc->kf, "File Manager"))
        {
            fc->group = "File Manager";
            return fc;
        }
        g_key_file_free(fc->kf);
    }
    g_free(fc->filepath);
    fc->filepath = NULL;
    fc->group = fm_path_to_str(path);
    G_LOCK(cache);
    fc->kf = fc_cache;
    return fc;
}
