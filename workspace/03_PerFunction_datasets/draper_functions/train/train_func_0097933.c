vhttplog(fmt, args)
CONST char *fmt;
va_list args;
{
	XFILE *fp;

	if (!logheader || !htmllogfile) ;
	else if (!httplogfile || strpathcmp(httplogfile, htmllogfile))
		htmllog(logheader);
	if (!httplogfile || !isrootdir(httplogfile)) return;
	if (!(fp = Xfopen(httplogfile, "a"))) return;
	if (logheader) {
		Xfputs(logheader, fp);
		Xfree(logheader);
		logheader = NULL;
	}
	VOID_C Xvfprintf(fp, fmt, args);
	VOID_C Xfclose(fp);
}
