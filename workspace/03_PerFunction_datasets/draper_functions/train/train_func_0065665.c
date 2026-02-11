log_uip(char *level_str, char *fmt, ...)
{
	char time_buf[32];
	va_list ap, ap2;

	pthread_mutex_lock(&main_log.lock);
	va_start(ap, fmt);

	if (main_log.fp == NULL)
		goto end;

	main_log.stats.last_log_time = time(NULL);
	strftime(time_buf, 26, "%a %b %d %T %Y",
		 localtime(&main_log.stats.last_log_time));
	va_copy(ap2, ap);

	if (main_log.enabled == LOGGER_ENABLED) {
		fprintf(main_log.fp, "%s [%s]", level_str, time_buf);
		vfprintf(main_log.fp, fmt, ap);
		fprintf(main_log.fp, "\n");
	}

	if (opt.debug == DEBUG_ON) {
		fprintf(stdout, "%s [%s]", level_str, time_buf);
		vfprintf(stdout, fmt, ap2);
		fprintf(stdout, "\n");


		fflush(main_log.fp);


		fflush(stdout);
	}

end:
	va_end(ap2);
	va_end(ap);
	pthread_mutex_unlock(&main_log.lock);
}
