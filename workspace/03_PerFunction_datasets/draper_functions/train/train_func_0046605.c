smartcmd_lookup(char *nam)
{
	int n = sizeof smarts / sizeof smarts[0];
	int i;

	for (i = 0; i < n; ++i) {
		char *p = strchr(nam, ':');

		if (p && !strncmp(smarts[i].name, nam, p - nam))
			return &smarts[i];
		else if (!strcmp(smarts[i].name, nam))
			return &smarts[i];
	}
	return nil;
}
