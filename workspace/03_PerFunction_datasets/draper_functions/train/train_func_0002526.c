log_msg_va(enum log_level lvl, int serr, const char *msg, va_list ap)
{
	if (lvl >= min_log_level) {
		vfprintf(log_file, msg, ap);
		if (serr)
			fprintf(log_file, ": %s", socket_error_string(-1));
		fputs("\n", log_file);
		fflush(log_file);
		if (lvl >= LOG_FATAL)
			abort();
	}
}
