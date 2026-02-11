has100(struct PCPnet *pcp, const char *kw)
{
	char *p=pcp->readbuf;
	int l = strlen(kw);

	while (*p)
	{
		while (isdigit((int)(unsigned char)*p))
			++p;
		if (*p != '\n')
			++p;

		if (strncasecmp(p, kw, l) == 0 &&
		    (p[l] == 0 || isspace((int)(unsigned char)p[l])))
			return (1);

		while (*p)
			if (*p++ == '\n')
				break;
	}
	return (0);
}
