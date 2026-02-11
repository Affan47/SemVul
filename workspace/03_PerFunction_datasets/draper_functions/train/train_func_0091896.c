path_is_dir(const char* path) {
    struct stat st;
    if (stat(path, &st)) {
        SYSERROR("Couldn't stat path %s", path);
        return FALSE;
    }

    return S_ISDIR(st.st_mode);
}
