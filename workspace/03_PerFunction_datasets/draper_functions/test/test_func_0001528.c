rfc2231_attrCreate(const char *name, const char *value,
		       const char *charset,
		       const char *language,
		       int (*cb_func)(const char *param,
				      const char *value,
				      void *void_arg),
		       void *cb_arg)
{
	size_t l;
	const char *cp;
	char *p, *q;
	int rc;

	if (strlen(name)>60)
	{
		errno=EINVAL;
		return -1;
	}

	for (l=0; value[l]; l++)
		if (DOENCODE(value[l]))
			break;

	if (value[l] == 0 && strlen(name)+strlen(value)<75)
	{
		char *p=malloc(strlen(value)+3);

		if (!p)
			return -1;

		strcat(strcat(strcpy(p, "\""), value), "\"");

		rc=(*cb_func)(name, p, cb_arg);
		free(p);
		return rc;
	}

	if (!charset) charset="";
	if (!language) language="";

	l=strlen(charset)+strlen(language)+strlen(value)+3;

	for (cp=value; *cp; cp++)
		if (DOENCODE(*cp))
			l += 2;

	p=malloc(l);
	if (!p)
		return -1;

	strcat(strcat(strcat(strcpy(p, charset), "'"),language), "'");
	q=p+strlen(p);
	for (cp=value; *cp; cp++)
	{
		if (DOENCODE(*cp))
		{
			*q++='%';
			*q++ = xdigit[ ((unsigned char)*cp / 16) & 15];
			*q++ = xdigit[ *cp & 15];
		}
		else
			*q++= *cp;
	}
	*q=0;

	rc=docreate(name, p, cb_func, cb_arg);
	free(p);
	return rc;
}
