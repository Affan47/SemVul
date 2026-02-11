write_log(int is_error, char *format, ...)
{
	va_list args;
	int n;
	char buf[2048];
	va_start(args, format);
	n = vsnprintf(buf, sizeof(buf), format, args);
	va_end(args);

	if(n < 1)
		return;

	if(log_mode)
		syslog(is_error?LOG_WARNING:LOG_INFO, buf);
	if(is_error || print_mode)
		fprintf(is_error?stderr:stdout, "%s: %s\n", argv0, buf);
}
