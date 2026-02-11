log_buf(int severity, char *buf)
{
	if (severity == LOG_DEBUG && !debug)
		return;
	if (log_destination == LOG_TERMINAL) {
		fprintf(stderr, "%s: %s\n", prio2str(severity),buf);
	} else {
		cl_log(severity, "%s", buf);
	}
}
