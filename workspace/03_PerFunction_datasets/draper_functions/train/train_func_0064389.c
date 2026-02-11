get_next_header(FILE *fp, char **value,
			     int preserve_nl,
			     off_t *mimepos, const off_t *endpos)
{
	int	c;
	int	eatspaces=0;

	size_t bufsize=256;
	char *buf=malloc(bufsize);
	size_t buflen=0;

	if (!buf)
		return NULL;

	if (mimepos && *mimepos >= *endpos)	return (NULL);

	while (mimepos == 0 || *mimepos < *endpos)
	{
		if ((c=getc(fp)) != '\n' && c >= 0)
		{
			if (c != ' ' && c != '\t' && c != '\r')
				eatspaces=0;

			if (!eatspaces)
				addbuf(c, &buf, &bufsize, &buflen);
			if (mimepos)	++ *mimepos;
			continue;
		}
		if ( c == '\n' && mimepos)	++ *mimepos;
		if (buflen == 0)
		{
			free(buf);
			return (0);
		}
		if (c < 0)	break;
		c=getc(fp);
		if (c >= 0)	ungetc(c, fp);
		if (c < 0 || c == '\n' || !isspace(c))	break;
		addbuf(preserve_nl ? '\n':' ', &buf, &bufsize, &buflen);
		if (!preserve_nl)
			eatspaces=1;
	}
	addbuf(0, &buf, &bufsize, &buflen);
	buf[buflen-1]=0;

	for ( *value=buf; **value; (*value)++)
	{
		if (**value == ':')
		{
			**value='\0';
			++*value;
			break;
		}
		**value=tolower(**value);
	}
	while (**value && isspace((int)(unsigned char)**value))	++*value;
	return(buf);
}
