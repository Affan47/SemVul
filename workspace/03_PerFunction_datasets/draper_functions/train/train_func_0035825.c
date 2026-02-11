outChar(const char* str, ...)
{
    if (!str)
        return;

    if (charLogfile)
    {
        va_list ap;
        outTimestamp(charLogfile);
        va_start(ap, str);
        vfprintf(charLogfile, str, ap);
        fprintf(charLogfile, "\n");
        va_end(ap);
        fflush(charLogfile);
    }
}
