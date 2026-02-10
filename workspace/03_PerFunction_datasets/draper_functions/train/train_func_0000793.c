dSncpy(String *dest, const char *src, int n, const char *file, int line)
{
    int len = strlen(src);

    if (n < 0) core("dSncpy: n==%ld", file, line, (long)n);
    if (n > len) n = len;
    dest->len = n;
    if (dest->charattrs) {
        Sfree(dest, dest->charattrs);
        dest->charattrs = NULL;
    }
    lcheck(dest, file, line);
    memcpy(dest->data, src, n);
    dest->data[n] = '\0';
    return dest;
}
