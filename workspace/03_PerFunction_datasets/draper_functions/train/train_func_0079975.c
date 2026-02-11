str_format(const char* format, ...) {
#else
	string str_format(va_list format, ...) {
#endif
	va_list ap;
	va_start(ap, format);
	string result;
	str_format(&result, (const char*)format, ap);
	va_end(ap);
	return result;
}
