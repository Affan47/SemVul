hkl_error_new (const char *format, ...)
{
	HklError* error;
	va_list args;

	if (!format)
		return NULL;

	va_start (args, format);
	error = hkl_error_new_valist (format, args);
	va_end (args);

	return error;
}
