find_shader(const char *name) {

    fs_log("checking shader %s\n", name);
    if (fs_path_exists(name)) {
        return fs_strdup(name);
    }
    char *name2 = fs_strconcat(name, ".shader", NULL);
    char *path = fs_path_join("shaders", name2, NULL);
    free(name2);
    fs_log("checking shader (share)/%s\n", path);
    char *path2 = fs_get_program_data_file(path);
    free(path);
    if (path2) {
        return path2;
    }
    return NULL;
}
