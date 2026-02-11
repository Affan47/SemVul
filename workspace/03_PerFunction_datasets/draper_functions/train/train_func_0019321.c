vftplog(fmt, args)
CONST char *fmt;
va_list args;
{
	XFILE *fp;

	if (!ftplogfile || !isrootdir(ftplogfile)) return;
	if (!(fp = Xfopen(ftplogfile, "a"))) return;
	if (logheader) {
		Xfputs(logheader, fp);
		Xfree(logheader);
		logheader = NULL;
	}
	VOID_C Xvfprintf(fp, fmt, args);
	VOID_C Xfclose(fp);
}
