fs_ini_file_open(const char *path) {
    fs_ini_file *ini_file = fs_ini_file_create();

    int result = ini_parse(path, handler, ini_file);
    if (result == -1) {

        fs_ini_file_destroy(ini_file);
        return NULL;
    }

    return ini_file;
}
