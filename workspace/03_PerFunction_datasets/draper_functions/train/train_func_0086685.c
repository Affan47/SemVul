vdebugOut(const char *fmt, va_list args)
{
    if (debugMode)
    {
        (void)vfprintf(stderr, fmt, args);
    }
}
