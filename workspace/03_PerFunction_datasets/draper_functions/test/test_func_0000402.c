_log(const char* fmt, ...)
{
    if (verbose_level < 1)
        return;

    va_list args;
    va_start(args, fmt);
    vfprintf(stdout, fmt, args);
    va_end(args);
    fflush(stdout);
}
