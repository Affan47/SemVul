create_items_path(const char *s, char *buf, size_t size) {
    char *t;

    if (*s == '/')
        s++;

    snprintf(buf, size, "%s/%s/", settings.localdir, settings.uniquedir);
    t = buf+strlen(buf);
    snprintf(t, buf+size-t, "%s", s);

    while (*t != '\0') {
        if (*t == '/')
            *t = '@';
        t++;
    }
}
