load_contrprocinfo(int *lastcontrp)
{
	static char *fn = "/proc/capi/controller";
	struct contrprocinfo *list, *p, **pp;
	char buf[4096];
	FILE *fp;
	int line = 0;

	if (lastcontrp)
		*lastcontrp = 0;
	list = 0;
	if ((fp = fopen_with_errmsg(fn, "r")) == NULL)
		return 0;
	while (fgets(buf,sizeof(buf),fp)) {
		char *s, *tmp, *target;
		line++;
		if ((p = STRUCTALLOC(struct contrprocinfo)) == 0) {
			fprintf(stderr, "ERROR: %s:%d: malloc failed\n", fn, line);
			goto error;
		}
		memset(p, 0, sizeof(*p));
		s = buf;

		tmp = s;
		p->contr = strtol(s, &tmp, 10);
		if (tmp == s) goto parseerror;

		target = skip_whitespace(tmp);
		s = skip_nonwhitespace(target);
		if (!*s) goto parseerror;
		*s++ = 0;
		snprintf(p->driver, sizeof(p->driver), "%s", target);

		target = skip_whitespace(s);
		s = skip_nonwhitespace(target);
		if (!*s) goto parseerror;
		*s++ = 0;
		p->state = str2cardstate(target);

		target = skip_whitespace(s);
		s = skip_nonwhitespace(target);
		if (!*s) goto parseerror;
		*s++ = 0;
		snprintf(p->name, sizeof(p->name), "%s", target);

		target = skip_whitespace(s);
		while (*s && *s != '\n') s++;
		if (*s) *s = 0;
		snprintf(p->driverinfo, sizeof(p->driverinfo), "%s", target);

		for (pp = &list; *pp; pp = &(*pp)->next) ;
		*pp = p;
		if (lastcontrp && *lastcontrp < p->contr)
			*lastcontrp = p->contr;
	}
	fclose(fp);
	return list;
parseerror:
	fprintf(stderr, "ERROR: %s:%d: parse error\n", fn, line);
error:
	fclose(fp);
	free_contrprocinfo(&list);
	return 0;
}
