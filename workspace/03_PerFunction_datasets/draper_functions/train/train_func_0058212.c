regname_ok(const char *s, const char *eos)
{
	while (s && s<eos) {
		if (CHAR_IS_UNRESERVED(*s) ||
		    strchr(SUBDELIMS, *s))
			++s;
		else if (*s == '%' &&
		    EVUTIL_ISXDIGIT_(s[1]) &&
		    EVUTIL_ISXDIGIT_(s[2]))
			s += 3;
		else
			return 0;
	}
	return 1;
}
