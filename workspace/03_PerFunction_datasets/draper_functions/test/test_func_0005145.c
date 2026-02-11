logmsg(const char *msg, ...)
{
	va_list ap;
	va_start(ap, msg);
	if (logging_to_syslog)
		vsyslog(LOG_CRIT, msg, ap);
	else {
		vfprintf(stderr, msg, ap);
		fputc('\n', stderr);
	}
	va_end(ap);
	return;
}
