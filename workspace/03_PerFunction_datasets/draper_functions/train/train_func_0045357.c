xfmt_has_quotes(const char *text)
{
	const char *p = text;
	int c;
	int flags = 0;

	g_assert(text != NULL);


	while ('\0' != (c = *p++)) {
		if ('\'' == c) {
			flags |= XFMT_M_SINGLE;
			if (XFMT_M_BOTH == flags)
				break;
		} else if ('"' == c) {
			flags |= XFMT_M_DOUBLE;
			if (XFMT_M_BOTH == flags)
				break;
		}
	}

	return flags;
}
