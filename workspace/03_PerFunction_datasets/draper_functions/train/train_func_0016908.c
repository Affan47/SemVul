awk_printf(node *n)
{
	char *b = NULL;
	char *fmt, *s, *f;
	const char *s1;
	int i, j, incr, bsize;
	char c, c1;
	var *v, *arg;

	v = nvalloc(1);
	fmt = f = xstrdup(getvar_s(evaluate(nextarg(&n), v)));

	i = 0;
	while (*f) {
		s = f;
		while (*f && (*f != '%' || *++f == '%'))
			f++;
		while (*f && !isalpha(*f)) {
			if (*f == '*')
				syntax_error("%*x formats are not supported");
			f++;
		}

		incr = (f - s) + MAXVARFMT;
		b = qrealloc(b, incr + i, &bsize);
		c = *f;
		if (c != '\0')
			f++;
		c1 = *f;
		*f = '\0';
		arg = evaluate(nextarg(&n), v);

		j = i;
		if (c == 'c' || !c) {
			i += sprintf(b+i, s, is_numeric(arg) ?
					(char)getvar_i(arg) : *getvar_s(arg));
		} else if (c == 's') {
			s1 = getvar_s(arg);
			b = qrealloc(b, incr+i+strlen(s1), &bsize);
			i += sprintf(b+i, s, s1);
		} else {
			i += fmt_num(b+i, incr, s, getvar_i(arg), FALSE);
		}
		*f = c1;


		if (i < j)
			i = j;
	}

	free(fmt);
	nvfree(v);
	b = xrealloc(b, i + 1);
	b[i] = '\0';
	return b;
}
