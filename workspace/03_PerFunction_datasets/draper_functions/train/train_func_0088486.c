size_to_human_string(int options, uint64_t bytes)
{
	char buf[32];
	int dec, exp;
	uint64_t frac;
	const char *letters = "BKMGTPE";
	char suffix[sizeof(" KiB")], *psuf = suffix;
	char c;

	if (options & SIZE_SUFFIX_SPACE)
		*psuf++ = ' ';

	exp  = get_exp(bytes);
	c    = *(letters + (exp ? exp / 10 : 0));
	dec  = exp ? bytes / (1ULL << exp) : bytes;
	frac = exp ? bytes % (1ULL << exp) : 0;

	*psuf++ = c;

	if ((options & SIZE_SUFFIX_3LETTER) && (c != 'B')) {
		*psuf++ = 'i';
		*psuf++ = 'B';
	}

	*psuf = '\0';


	if (frac) {

		frac = (frac / (1ULL << (exp - 10)) + 50) / 100;
		if (frac == 10)
			dec++, frac = 0;
	}

	if (frac) {
		struct lconv const *l = localeconv();
		char *dp = l ? l->decimal_point : NULL;

		if (!dp || !*dp)
			dp = ".";
		snprintf(buf, sizeof(buf), "%d%s%jd%s", dec, dp, frac, suffix);
	} else
		snprintf(buf, sizeof(buf), "%d%s", dec, suffix);

	return strdup(buf);
}
