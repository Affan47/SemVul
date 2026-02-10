regex_exec_match(const struct my_regex *preg, const char *subject,
                     size_t nmatch, regmatch_t pmatch[]) {
#if defined(USE_PCRE) || defined(USE_PCRE_JIT)
	int ret;
	int matches[MAX_MATCH * 3];
	int enmatch;
	int i;


	enmatch = nmatch;
	if (enmatch > MAX_MATCH)
		enmatch = MAX_MATCH;


	ret = pcre_exec(preg->reg, preg->extra, subject, strlen(subject), 0, 0, matches, enmatch * 3);
	if (ret < 0)
		return 0;

	if (ret == 0)
		ret = enmatch;

	for (i=0; i<nmatch; i++) {

		if (i < ret) {
			pmatch[i].rm_so = matches[(i*2)];
			pmatch[i].rm_eo = matches[(i*2)+1];
			continue;
		}

		pmatch[i].rm_so = -1;
		pmatch[i].rm_eo = -1;
	}
	return 1;
#else
	int match;
	match = regexec(&preg->regex, subject, nmatch, pmatch, 0);
	if (match == REG_NOMATCH)
		return 0;
	return 1;
#endif
}
