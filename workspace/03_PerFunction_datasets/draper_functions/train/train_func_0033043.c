event_logv_(int severity, const char *errstr, const char *fmt, va_list ap)
{
	char buf[1024];
	size_t len;

	if (severity == EVENT_LOG_DEBUG && !event_debug_get_logging_mask_())
		return;

	if (fmt != NULL)
		evutil_vsnprintf(buf, sizeof(buf), fmt, ap);
	else
		buf[0] = '\0';

	if (errstr) {
		len = strlen(buf);
		if (len < sizeof(buf) - 3) {
			evutil_snprintf(buf + len, sizeof(buf) - len, ": %s", errstr);
		}
	}

	event_log(severity, buf);
}
