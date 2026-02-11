rb_lib_log(const char *format, ...)
{
	va_list args;
	if(rb_log == NULL)
		return;
	va_start(args, format);
	rb_vsnprintf(errbuf, sizeof(errbuf), format, args);
	va_end(args);
	rb_log(errbuf);
}
