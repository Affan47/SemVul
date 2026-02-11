pcre_nmatchsize(CTX ctx, kregex_t *reg)
{
	PCRE_regex_t *preg = (PCRE_regex_t*)reg;
	int capsize = 0;
	if (_pcre_fullinfo(preg->re, NULL, PCRE_INFO_CAPTURECOUNT, &capsize) != 0) {
		return KREGEX_MATCHSIZE;
	}
	return capsize + 1;
}
