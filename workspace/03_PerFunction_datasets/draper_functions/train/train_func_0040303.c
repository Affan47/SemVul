stringprintf(const char* fmt, ...) {
	va_list vl;
	va_start(vl, fmt);
	size_t n = strlen(fmt)+1024;

	char* s = new char[n];
	vsnprintf(s, n, fmt, vl);
	va_end(vl);
	string ss(s);
	delete s;
	return ss;
}
