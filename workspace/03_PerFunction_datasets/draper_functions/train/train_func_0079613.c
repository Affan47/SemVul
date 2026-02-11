string_append(char **s, const char *p) {
    if (*s == NULL) {
        *s = strdup(p);
    } else {
        int len = strlen(*s) + strlen(p) + 1;
        *s = realloc(*s, len);
        if (*s == NULL)
            die_oom();
        strcat(*s, p);
    }
}
