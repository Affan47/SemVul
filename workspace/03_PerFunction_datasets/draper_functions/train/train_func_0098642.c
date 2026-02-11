PILLog(PILLogLevel priority, const char * format, ...)
{
	va_list		args;
	GLogLevelFlags	flags;

	switch(priority) {
		case PIL_FATAL:	flags = G_LOG_LEVEL_ERROR;
			break;
		case PIL_CRIT:	flags = G_LOG_LEVEL_CRITICAL;
			break;

		default:
		case PIL_WARN:	flags = G_LOG_LEVEL_WARNING;
			break;

		case PIL_INFO:	flags = G_LOG_LEVEL_INFO;
			break;
		case PIL_DEBUG:	flags = G_LOG_LEVEL_DEBUG;
			break;
	};
	va_start (args, format);
	g_logv (G_LOG_DOMAIN, flags, format, args);
	va_end (args);
}
