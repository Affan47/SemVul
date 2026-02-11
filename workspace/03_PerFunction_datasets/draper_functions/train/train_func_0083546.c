bofh_checkspf(const char *envvarname,
		  const char *defaultValue, const char *keyword)
{
	char buf[256];
	const char *p=getenv(envvarname);
	char *s;

	if (!p || !*p) p=defaultValue;

	buf[0]=0;
	strncat(buf, p, sizeof(buf)-1);

	for (s=buf; (s=strtok(s, ",")) != NULL; s=NULL)
		if (strcmp(s, keyword) == 0)
			return 1;
	return 0;
}
