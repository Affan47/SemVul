fs_str_has_prefix(const char *str, const char *prefix) {
    int str_len;
    int prefix_len;

    if (str == NULL) {
        return 0;
    }
    if (prefix == NULL) {
        return 0;
    }

    str_len = strlen(str);
    prefix_len = strlen(prefix);

    if (str_len < prefix_len) return FALSE;

    return strncmp(str, prefix, prefix_len) == 0;
}
