vrdval(const char* p, const char* key,
	enum conv_type conv, ullong *vec, va_list arg_ptr)
{
	int indexline;
	int indexnext;

	p = strstr(p, key);
	if (!p) return 1;

	p += strlen(key);
	indexline = 1;
	indexnext = va_arg(arg_ptr, int);
	while (1) {
		while (*p == ' ' || *p == '\t') p++;
		if (*p == '\n' || *p == '\0') break;

		if (indexline == indexnext) {
			*vec++ = conv==conv_decimal ?
				strtoull(p, NULL, 10) :
				read_after_slash(p);
			indexnext = va_arg(arg_ptr, int);
		}
		while (*p > ' ') p++;
		indexline++;
	}
	return 0;
}
