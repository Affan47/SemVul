log_debug(int cls, int level, const char *fmt, ...)
{
	va_list         ap;


	if (cls >= 0 && (log_level[cls] == 0 || level > log_level[cls]))
		return;
	va_start(ap, fmt);
	_log_print(0, LOG_INFO, fmt, ap, cls, level);
	va_end(ap);
}
