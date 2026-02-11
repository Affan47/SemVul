http_value_collect(const char *start, char *value, size_t len)
{
	size_t pos = 0;
	const char *p = start;
	bool has_quote = FALSE;
	int c;

	g_assert(value != NULL);
	g_assert(size_is_non_negative(len));

	c = *p;
	if ('"' == c) {
		has_quote = TRUE;
		p++;
	}

	while ('\0' != (c = *p++) && pos < len) {
		if ('"' == c) {
			if (has_quote)
				goto ok;
			return FALSE;
		} else if ('\\' == c) {
			c = *p++;
			if ('\0' == c)
				return FALSE;
		}
		value[pos++] = c;
	}

	if (has_quote)
		return FALSE;

	if (pos == len)
		return FALSE;

ok:
	g_assert(pos < len);

	value[pos] = '\0';
	return TRUE;
}
