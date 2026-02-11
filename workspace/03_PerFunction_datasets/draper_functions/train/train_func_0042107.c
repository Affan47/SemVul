go_regexp_quote1 (GString *target, const char *s)
{
	g_return_val_if_fail (target != NULL, NULL);
	g_return_val_if_fail (s != NULL, NULL);

	switch (*s) {
	case '.': case '[': case '\\':
	case '*': case '+': case '{': case '?':
	case '^': case '$':
	case '(': case '|': case ')':
		g_string_append_c (target, '\\');
		g_string_append_c (target, *s);
		return s + 1;

	case 0:
		return s;

	default:
		do {
			g_string_append_c (target, *s);
			s++;
		} while ((*s & 0xc0) == 0x80);

		return s;
	}
}
