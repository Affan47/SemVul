_xalloc_warn(const char *fmt, ...)
{
	va_list ap;

	if (debug_output == NULL)
		debug_output = XALLOC_DEFAULT_OUTPUT;

	va_start(ap, fmt);
#ifndef XALLOC_SILENT
	vfprintf(debug_output, fmt, ap);
	fflush(debug_output);
#endif
	va_end(ap);
}
