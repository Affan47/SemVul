control_escape(const char *s)
{
	size_t need_escape = 0;
	const char *p;
	uchar c;

	for (p = s; '\0' != (c = *p); p++)
		if (escape_control_char(c))
			need_escape++;

	if (need_escape > 0) {
		char *q, *escaped;

		q = escaped = halloc(p - s + 1 + 3 * need_escape);

		for (p = s; '\0' != (c = *p); p++) {
			if (escape_control_char(c)) {
				if ('\r' == c && '\n' == p[1]) {

				} else {
					*q++ = escape_char;
					*q++ = 'x';
					*q++ = hex_alphabet[c >> 4];
					*q++ = hex_alphabet[c & 0xf];
				}
			} else {
				*q++ = c;
			}
		}
		*q = '\0';

		return escaped;
	}

	return deconstify_gchar(s);
}
