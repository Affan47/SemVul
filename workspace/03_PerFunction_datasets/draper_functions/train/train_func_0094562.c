regexp_match(const char *str, const char *regexp)
{
#ifdef HAVE_REGEX_H
	regex_t preg;
	int ret;

	if (regcomp(&preg, regexp, REG_EXTENDED|REG_ICASE|REG_NOSUB) != 0)
                return 0;

	ret = regexec(&preg, str, 0, NULL, 0);
	regfree(&preg);

	return ret == 0;
#else
	return FALSE;
#endif
}
