cha_exit(int status, char *format, ...)
{
    va_list ap;

    if (Cha_errno)
	return;

    if (!cha_stderr)
	cha_stderr = stderr;
    else if (cha_stderr != stderr)
	fputs("500 ", cha_stderr);

    if (progpath)
	fprintf(cha_stderr, "%s: ", progpath);
    va_start(ap, format);
    vfprintf(cha_stderr, format, ap);
    va_end(ap);
    if (status >= 0) {
	fputc('\n', cha_stderr);
	if (cha_stderr == stderr)
	    exit(status);
	Cha_errno = 1;
    }
}
