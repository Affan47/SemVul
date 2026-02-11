getstr(const char * cmd, int el) {
    char *work, *s, *t, *r;
    char *peek;
    int i = 0;

    work = strdup(cmd);
    s = t = work;
    r = NULL;

    peek = s;
    if (peek)
        peek++;
    while (*s) {
        if (*s == '\t' || *s == '\0') {
            if (i == el) {
                if (*peek != '\0' || *s == '\t')
                    *s = '\0';
                r = strdup(t);
                free(work);
                return r;
            } else {
                i++;
                s++;
                peek++;
                t = s;
            }
        }
        s++;
        peek++;
    }

    if (t) r = strdup(t);
    free(work);
    return r;
}
