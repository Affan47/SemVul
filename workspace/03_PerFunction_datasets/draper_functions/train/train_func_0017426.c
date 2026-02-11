escape_string(const char *s)
{
	const char *p;
	char *q, *r;
	size_t size;

	if (s == NULL)
		return NULL;

	p = s;
	size = 0;
	while (*p != '\0') {
		if (*p == '"' || *p == '\\' || *p == '\'') {
			size += 2;
		} else {
			size++;
		}
		p++;
	}

	p = s;
	r = q = xmalloc(size + 1);
	while (*p != '\0') {
		if (*p == '"' || *p == '\\' || *p == '\'') {
			*q++ = '\\';
			*q++ = *p++;
		} else {
			*q++ = *p++;
		}
	}
	*q++ = '\0';
	return r;
}
