reg_match(char *pattern, char *string, regmatch_t *pmatch)
{
	regex_t preg;

	if (regcomp(&preg, pattern, REG_EXTENDED | REG_NEWLINE)) {
		return -1;
	}
	if (preg.re_nsub > MAX_MATCH) {
		regfree(&preg);
		return -2;
	}
	if (regexec(&preg, string, MAX_MATCH, pmatch, 0)) {
		regfree(&preg);
		return -3;
	}
	regfree(&preg);
	return 0;
}
