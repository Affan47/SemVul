nsyslog(int pri, char *fmt, ...)
{
	va_list  args;

	va_start(args, fmt);

	if (ttyname(0) == NULL) {
		vsyslog(pri, fmt, args);
	} else {
		fprintf(stderr, "%s: ",progname);
		vfprintf(stderr, fmt, args);
		fprintf(stderr, "\n");
	}

	va_end(args);
}
