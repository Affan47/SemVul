GracePrintf(const char* fmt, ...)
{
    va_list ap;
    char* str;
    int nchar;

    if (fd_pipe == -1) {
        error_function("No grace subprocess4");
        return (0);
    }


    str = (char *) malloc ((size_t) bufsize);
    if (str == (char *) NULL) {
        error_function("GracePrintf: Not enough memory");
        return (0);
    }

    va_start (ap, fmt);
#if defined(HAVE_VSNPRINTF)
    nchar = vsnprintf (str, bufsize - 2, fmt, ap);
#else
    nchar = vsprintf (str, fmt, ap);
#endif
    va_end (ap);
    nchar++;
    if (GraceCommand (str) == -1) {
        nchar = 0;
    }
    free (str);
    return (nchar);
}
