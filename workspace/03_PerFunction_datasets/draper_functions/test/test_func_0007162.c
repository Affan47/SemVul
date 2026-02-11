cha_exit_file(int status, char *format, ...)
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

    if (Cha_lineno == 0)
	;
    else if (Cha_lineno == Cha_lineno_error)
	fprintf(cha_stderr, "%s:%d: ", filepath, Cha_lineno);
    else
	fprintf(cha_stderr, "%s:%d-%d: ", filepath, Cha_lineno_error,
		Cha_lineno);

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
