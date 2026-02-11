fs_uae_documents_dir() {
    static const char* path = NULL;
    if (path == NULL) {
        path = fs_get_documents_dir();
        if (path == NULL) {
            fs_log("WARNING: did not find documents directory\n");
            path = fs_uae_home_dir();
        }
        int result = fs_mkdir_with_parents(path, 0755);
        if (result == -1) {
            char *msg = fs_strdup_printf("Documents directory does not "
                    "exist: %s", path);
            fs_emu_warning(msg);
            free(msg);
            path = fs_uae_home_dir();
        }
        fs_log("- using documents directory \"%s\"\n", path);
    }
    return path;
}
