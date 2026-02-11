g_set_logdest(log_opt_t _logdest, ...)
{
	va_list va;

	logdest = _logdest;

	va_start(va, _logdest);
	if (logdest == G_LOG_FILE) logfile = va_arg(va, char *);
	else logfile = NULL;
	va_end(va);

	if (logdest == G_LOG_SYSLOG) openlog(APPNAME, LOG_PID, LOG_USER);
}
