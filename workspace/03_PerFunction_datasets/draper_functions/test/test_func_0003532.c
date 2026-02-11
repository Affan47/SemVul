Symbol_hack(const char *a0)
{
	char buf[BUFSIZ], *p, *e;
	FILE *fi;
	uintptr_t a;
	struct symbols *s;

	bprintf(buf, "nm -an %s 2>/dev/null", a0);
	fi = popen(buf, "r");
	if (fi == NULL)
		return;
	while (fgets(buf, sizeof buf, fi)) {
		if (buf[0] == ' ')
			continue;
		p = NULL;
		a = strtoul(buf, &p, 16);
		if (p == NULL)
			continue;
		if (a == 0)
			continue;
		if (*p++ != ' ')
			continue;
		p++;
		if (*p++ != ' ')
			continue;
		if (*p <= ' ')
			continue;
		e = strchr(p, '\0');
		AN(e);
		while (e > p && isspace(e[-1]))
			e--;
		*e = '\0';
		s = malloc(sizeof *s + strlen(p) + 1);
		AN(s);
		s->a = a;
		s->n = (void*)(s + 1);
		strcpy(s->n, p);
		VTAILQ_INSERT_TAIL(&symbols, s, list);
	}
	(void)pclose(fi);
}
