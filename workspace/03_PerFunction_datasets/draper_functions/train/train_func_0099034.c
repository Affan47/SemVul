g_web_set_accept(GWeb *web, const char *format, ...)
{
	va_list args;
	gboolean result;

	if (web == NULL)
		return FALSE;

	va_start(args, format);
	result = set_accept_option(web, format, args);
	va_end(args);

	return result;
}
