talloc_vasprintf(const void *t, const char *fmt, va_list ap)
{
	int len;
	char *ret;
	va_list ap2;
	char c;


	va_copy(ap2, ap);
	len = vsnprintf(&c, 1, fmt, ap2);
	va_end(ap2);
	if (unlikely(len < 0)) {
		return NULL;
	}

	ret = (char *)__talloc(t, len+1);
	if (unlikely(!ret)) return NULL;

	va_copy(ap2, ap);
	vsnprintf(ret, len+1, fmt, ap2);
	va_end(ap2);

	_talloc_set_name_const(ret, ret);
	return ret;
}
