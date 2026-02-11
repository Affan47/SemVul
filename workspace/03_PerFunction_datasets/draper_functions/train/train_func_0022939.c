strn_catf(char* dst, size_t size, const char* format, ...)
{
    int ret;
    va_list args;
#ifdef _GNU_SOURCE
    int len = strnlen(dst,size);
#else
    int len = strlen(dst);
#endif

    if (len >= size) {
	string_overflow_handler("Buffer already overflowed '%.*s'\n",
				size, dst);
    }
    va_start(args, format);
    ret = vsn_printf(dst+len, size-len, format, args);
    va_end(args);
    return len+ret;
}
