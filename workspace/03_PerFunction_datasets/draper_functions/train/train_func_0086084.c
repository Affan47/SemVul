chkdelto(FILE *f, const char *delivto)
{
char	buf[BUFSIZ];
char	*p, *q;


	while ((p=fgets(buf, sizeof(buf), f)) != 0)
	{
		if ((p=strchr(buf, '\n')) != 0)
			*p=0;
		else
		{
		int	c;

			while ((c=getc(f)) >= 0 && c != '\n')
				;
		}

		if (buf[0] == '\0')	break;
		if ((p=strchr(buf, ':')) == 0)	continue;
		*p++=0;
		for (q=buf; *q; q++)
			*q=tolower(*q);
		if (strcmp(buf, "delivered-to"))	continue;
		while (*p == ' ')
			++p;
		if (strcmp(p, delivto) == 0)
			return (1);
	}
	return (0);
}
