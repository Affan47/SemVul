scheme_ok(const char *s, const char *eos)
{

	EVUTIL_ASSERT(eos >= s);
	if (s == eos)
		return 0;
	if (!EVUTIL_ISALPHA(*s))
		return 0;
	while (++s < eos) {
		if (! EVUTIL_ISALNUM(*s) &&
		    *s != '+' && *s != '-' && *s != '.')
			return 0;
	}
	return 1;
}
