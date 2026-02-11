lprintf(FILE *max, ...)
  {
    va_list  args;
    char     *fmt;
    char     buff[300];

    va_start(args, max);

    fmt = va_arg(args, char *);
    (void) vsprintf(buff, fmt, args);
    va_end(args);
    (void) fputs(buff, max);

    if (logfile != NULL)
	logprint(buff);
  }
