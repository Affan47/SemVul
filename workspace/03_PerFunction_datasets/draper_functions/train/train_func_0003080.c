search_boundary(FILE *f, const char *b, int *bit8flag)
{
char	buf[BUFSIZ];
size_t	l=strlen(b);
const char *p;
int	flag=0;
int	cr;

	if (fseek(f, 0L, SEEK_SET))	return (-1);

	while (fgets(buf, sizeof(buf), f))
	{
		if (buf[0] == '-' && buf[1] == '-' &&

#if	HAVE_STRNCASECMP
			strncasecmp(buf+2, b, l)
#else
			strnicmp(buf+2, b, l)
#endif
			 == 0)	flag=1;

		cr=0;
		for (p=buf; *p; p++)
			if (*p == '\n')	cr=1;
			else if ((int)(unsigned char)*p >= 127)
				*bit8flag=1;

		if (!cr)
		{
		int	c;

			while ((c=getc(f)) >= 0 && c != '\n')
				if ((int)(unsigned char)c >= 127)
					*bit8flag=1;
		}
	}
	return (flag);
}
