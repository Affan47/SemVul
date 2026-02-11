error_raw(char *s, ...)
{
    va_list         ap;
    char            *buffer;

    va_start(ap, s);
    buffer = vmprintf_errok(s, ap);
    if (!buffer)
        double_jeopardy();
    va_end(ap);
    wrap(buffer);
}
