str_ncat_safe(str_t *str, const char *string, size_t len)
{
	char *p;
	const char *q;
	char c;
	bool fits = TRUE;

	str_check(str);
	g_assert(string != NULL);
	g_assert(size_is_non_negative(len));

	if G_UNLIKELY(0 == len)
		return TRUE;

	if G_UNLIKELY(str->s_flags & STR_FOREIGN_PTR) {
		size_t n;

		if (str->s_len == str->s_size) {
			return FALSE;
		} else {
			n = size_saturate_add(len, str->s_len);

			if (n >= str->s_size) {
				fits = FALSE;
				len = str->s_size - str->s_len - 1;
				if (0 == len)
					return FALSE;
			}
		}
	} else {
		str_makeroom(str, len + 1);
	}

	p = str->s_data + str->s_len;
	q = string;

	while (len > 0 && '\0' != (c = *q++)) {
		*p++ = c;
		len--;
	}

	str->s_len = p - str->s_data;
	return fits;
}
