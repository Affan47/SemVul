bufappend(const char *s)
{
    if (!buf)
        buf = malloc(sizeof(*buf) * p);
    while (*s) {
        buf[n++] = *s;
        s++;
        if (n == p)
            buf = realloc(buf, sizeof(*buf) * (p *= 1.5));
    }
    buf[n] = '\0';
}
