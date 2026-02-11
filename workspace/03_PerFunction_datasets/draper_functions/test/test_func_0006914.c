fs_uae_expand_path(const char* path) {
    char* lower = fs_ascii_strdown(path, -1);
    int replace = 0;
    const char *replace_with = NULL;

    if (fs_str_has_prefix(lower, "~/") || fs_str_has_prefix(lower, "~\\")) {
        replace = 2;
        replace_with = fs_uae_home_dir();
    }
    if (fs_str_has_prefix(lower, "$home/") ||
            fs_str_has_prefix(lower, "$home\\")) {
        replace = 6;
        replace_with = fs_uae_home_dir();
    }
    if (fs_str_has_prefix(lower, "$app/") ||
            fs_str_has_prefix(lower, "$app\\")) {
        replace = 5;
        replace_with = fs_uae_app_dir();
    }
    if (fs_str_has_prefix(lower, "$exe/") ||
            fs_str_has_prefix(lower, "$exe\\")) {
        replace = 5;
        replace_with = fs_uae_exe_dir();
    }
    if (fs_str_has_prefix(lower, "$fsuae/") ||
            fs_str_has_prefix(lower, "$fsuae\\")) {
        replace = 7;
        replace_with = fs_uae_base_dir();
    }
    if (fs_str_has_prefix(lower, "$base/") ||
            fs_str_has_prefix(lower, "$base\\")) {
        replace = 6;
        replace_with = fs_uae_base_dir();
    }
    if (fs_str_has_prefix(lower, "$documents/") ||
            fs_str_has_prefix(lower, "$documents\\")) {
        replace = 11;
        replace_with = fs_uae_documents_dir();
    }
    if (fs_str_has_prefix(lower, "$config/") ||
            fs_str_has_prefix(lower, "$config\\")) {
        replace = 8;
        replace_with = g_fs_uae_config_dir_path;
    }

    free(lower);
    if (replace && replace_with) {
        const char *src = path + replace;
        return fs_path_join(replace_with, src, NULL);
    }
    else {
        return fs_strdup(path);
    }
}
