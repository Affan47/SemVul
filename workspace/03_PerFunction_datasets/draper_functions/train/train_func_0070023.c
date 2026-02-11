use_config(char *m, int slen)
{
	char s[PATH_MAX];
	char *p;

	if (is_defined_config(m, slen))
	    return;

	define_config(m, slen);

	memcpy(s, m, slen); s[slen] = 0;

	for (p = s; p < s + slen; p++) {
		if (*p == '_')
			*p = '/';
		else
			*p = tolower((int)*p);
	}
	printf("    $(wildcard include/config/%s.h) \\\n", s);
}
