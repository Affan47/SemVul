msg(int level, const char *fmt, ...)
{
	int ret;
	va_list ap;

	if (level > verbosity)
		return 0;

	va_start(ap, fmt);

	if (level < MSG_QUIET)
		ret = vfprintf(stderr, fmt, ap);
	else
		ret = vfprintf(stdout, fmt, ap);

	va_end(ap);
	return ret;
}
