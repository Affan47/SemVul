file_putf(ang_file *f, const char *fmt, ...)
{
	va_list vp;
	bool status;

	if (!f) return FALSE;

	va_start(vp, fmt);
	status = file_vputf(f, fmt, vp);
	va_end(vp);

	return status;
}
