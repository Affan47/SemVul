fs_strdup_vprintf(const char *format, va_list args) {
    int n;
    int size = 100;
    char *p, *np;
    va_list ap;

    if ((p = malloc(size)) == NULL)
        return NULL;
    while (1) {
        va_copy(ap, args);
        n = vsnprintf(p, size, format, ap);
        va_end(ap);


        if (n > -1 && n < size)
            return p;


        if (n > -1)
            size = n+1;
        else
            size *= 2;

        if ((np = realloc (p, size)) == NULL) {
            free(p);
            return NULL;
        }
        else {
            p = np;
        }
    }
}
