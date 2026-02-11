printc_dbg(const char *fmt, ...)
{
	char buf[1024];
	va_list ap;

	if (opdb_get_boolean("quiet"))
		return 0;

	va_start(ap, fmt);
	vsnprintf(buf, sizeof(buf), fmt, ap);
	va_end(ap);

	return write_text(&stdout_buf, buf, stdout);
}
