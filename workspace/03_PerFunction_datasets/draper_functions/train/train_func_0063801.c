make_re_str(const char *s) {
    struct re_str *str;

    if (ALLOC(str) < 0)
        return NULL;
    if (s != NULL) {
        str->rx = strdup(s);
        str->len = strlen(s);
        if (str->rx == NULL) {
            FREE(str);
            return NULL;
        }
    }
    return str;
}
