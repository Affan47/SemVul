mkmsg(const char *fmt, ...)
{
    char buf[256];
    char *s;
    va_list ap;

    va_start(ap, fmt);
    vsprintf(buf, fmt, ap);
    va_end(ap);

    s = strdup(buf);
    if (s == 0) die("out of memory");
    return s;
}
