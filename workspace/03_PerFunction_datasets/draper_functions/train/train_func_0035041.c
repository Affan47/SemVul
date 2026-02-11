AWT_unfold_path(const char *path, const char *pwd_envar) {
    if (path[0] == '/' || path[0] == '~') return strdup(GB_get_full_path(path));
    return strdup(GB_concat_full_path(awt_get_base_directory(pwd_envar), path));
}
