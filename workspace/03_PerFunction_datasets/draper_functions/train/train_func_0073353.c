gl_logv(const char *domain, GLogLevelFlags flags, const char *fmt, va_list args)
{
	static str_t *msg;
	static bool logging;

	if (logging) {
		s_minilogv(flags | G_LOG_FLAG_RECURSION, FALSE, fmt, args);
		return;
	}


	logging = TRUE;

	if G_UNLIKELY(NULL == msg)
		msg = str_new_not_leaking(0);

	str_vprintf(msg, fmt, args);

	if (handler_cb != NULL)
		(*handler_cb)(domain, flags, str_2c(msg), handler_data);
	else
		s_minilog(flags, "%s", str_2c(msg));

	logging = FALSE;
}
