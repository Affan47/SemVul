logerror(const char *format, ...) {
	va_list ap;

	va_start(ap, format);
	if (amdaemon) {
		if (logfile != NULL)
			vfprintf(logfile, format, ap);
		else
			vsyslog(LOG_ERR, format, ap);
	} else {
		fputs(program, stderr);
		fputc(':', stderr);
		fputc(' ', stderr);
		vfprintf(stderr, format, ap);
	}
	va_end(ap);
}
