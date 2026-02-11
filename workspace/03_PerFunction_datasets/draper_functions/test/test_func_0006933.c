log_status_skip(LogInstance instance, const gchar *format, ...)
{
	va_list args;
	gchar buf[BUFFSIZE + LOG_TIME_LEN];
	time_t t;
	LogText *logtext = g_new0(LogText, 1);
	struct tm buft;

	time(&t);
	strftime(buf, LOG_TIME_LEN + 1, "[%H:%M:%S] ", localtime_r(&t, &buft));

	va_start(args, format);
	g_vsnprintf(buf + LOG_TIME_LEN, BUFFSIZE, format, args);
	va_end(args);

	if (debug_get_mode()) g_message("%s", buf + LOG_TIME_LEN);

	logtext->instance = instance;
	logtext->text = g_strdup(buf + LOG_TIME_LEN);
	logtext->type = LOG_STATUS_SKIP;

	g_timeout_add(0, invoke_hook_cb, logtext);

	if (log_fp[instance] && prefs_common_enable_log_status()) {
		FWRITE(buf, 1, LOG_TIME_LEN, log_fp[instance])
		FPUTS("* SKIPPED: ", log_fp[instance])
		log_size[instance] += strlen("* SKIPPED: ");
		FPUTS(buf + LOG_TIME_LEN, log_fp[instance])
		log_size[instance] += strlen(buf);
		FFLUSH(log_fp[instance])
		rotate_log(instance);
	}
}
