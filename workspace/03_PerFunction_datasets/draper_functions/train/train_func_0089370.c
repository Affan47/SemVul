format(const char* fmt ...)
{
    int size = DEFAULT_FORMAT_BUFFER;
    fxStr s;
    va_list ap;
    va_start(ap, fmt);
    s.data = (char*)malloc(size);
    int len = vsnprintf(s.data, size, fmt, ap);
    va_end(ap);
    while (len < 0 || len >= size) {
	if (len < 0 && errno != 0)
	    return s;
	if (len >= size) {
            size = len + 1;
        } else {
            size *= 2;
        }
        s.data = (char*)realloc(s.data, size);
        va_start(ap, fmt);
        len = vsnprintf(s.data, size, fmt, ap);
        va_end(ap);
    }
    if (size > len + 1) {
        s.data = (char*) realloc(s.data, len + 1);
    }
    s.slength = len + 1;
    return s;
}
