env_matches(struct envmatch *e)
{
	while (e) {
		int r;
		char *val = getenv(e->envname);
		if (!val)
			return 0;
		r = regexec(&e->match, val,  0,  NULL,  0);
		if (r != 0)
			return 0;
		e = e->next;
	}
	return 1;
}
