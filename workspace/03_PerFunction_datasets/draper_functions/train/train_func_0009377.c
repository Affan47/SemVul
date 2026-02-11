debug_log(const char* str, ...)
{
    if (!str)
        { return; }

    char buf[256];
    va_list ap;
    va_start(ap, str);
    vsnprintf(buf, 256, str, ap);
    va_end(ap);

    DEBUG_LOG("%s", buf);
}
