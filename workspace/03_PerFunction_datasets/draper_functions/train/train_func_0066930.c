Debug(int level, char *fmt, ...)
#else
Debug(level, fmt, va_alist)
    int level;
    char *fmt;
    va_dcl
#endif
{
    va_list ap;

    if (fDebug < level)
	return;
#if PROTOTYPES
    va_start(ap, fmt);
#else
    va_start(ap);
#endif
    if (isMultiProc)
	fprintf(stderr, "[%s] %s (%lu): DEBUG: [%s:%d] ",
		StrTime((time_t *)0), progname, (unsigned long)thepid,
		debugFileName, debugLineNo);
    else
	fprintf(stderr, "%s: DEBUG: [%s:%d] ", progname, debugFileName,
		debugLineNo);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    va_end(ap);
}
