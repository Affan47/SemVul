log_itf(const short type, const char *fmt, ...) {
	time_t lt = time(NULL);
	struct tm *now = localtime(&lt);

    if (type > max_log_level) {
        return;
    }

	pthread_mutex_lock(&log_lock);
	fprintf(log_file, "%d-%02d-%02d %02d:%02d:%02d %s: ",
			now->tm_year + 1900,
			now->tm_mon + 1,
			now->tm_mday,
			now->tm_hour,
			now->tm_min,
			now->tm_sec,
			log_level_labels[type]
			);

	va_list args;
	va_start(args, fmt);
	vfprintf(log_file, fmt, args);
	va_end(args);

	fputc('\n', log_file);
	fflush(log_file);

	pthread_mutex_unlock(&log_lock);
}
