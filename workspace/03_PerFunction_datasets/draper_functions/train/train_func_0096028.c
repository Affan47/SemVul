lperror(int level, const char * format, ...)
{
	static char logmsg[LOG_MSG_LENGTH];
	va_list vptr;

	if (!logpriv)
		log_reinit();

	if (logpriv->level < level)
		return;

	va_start(vptr, format);
	vsnprintf(logmsg, LOG_MSG_LENGTH, format, vptr);
	va_end(vptr);

	if (logpriv->daemon)
		syslog(level, "%s: %s", logmsg, strerror(errno));
	else
		fprintf(stderr, "%s: %s\n", logmsg, strerror(errno));
	return;
}
