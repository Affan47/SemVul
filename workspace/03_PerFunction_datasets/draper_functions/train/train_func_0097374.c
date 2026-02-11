pr_log __V((void *arg, char *fmt, ...))
{
	int l, n;
	va_list pvar;
	char *p, *eol;
	char buf[256];

#if defined(__STDC__)
	va_start(pvar, fmt);
#else
	void *arg;
	char *fmt;
	va_start(pvar);
	arg = va_arg(pvar, void *);
	fmt = va_arg(pvar, char *);
#endif

	n = vslprintf(buf, sizeof(buf), fmt, pvar);
	va_end(pvar);

	p = buf;
	eol = strchr(buf, '\n');
	if (linep != line) {
		l = (eol == NULL)? n: eol - buf;
		if (linep + l < line + sizeof(line)) {
			if (l > 0) {
				memcpy(linep, buf, l);
				linep += l;
			}
			if (eol == NULL)
				return;
			p = eol + 1;
			eol = strchr(p, '\n');
		}
		*linep = 0;
		log_write(llevel, line);
		linep = line;
	}

	while (eol != NULL) {
		*eol = 0;
		log_write(llevel, p);
		p = eol + 1;
		eol = strchr(p, '\n');
	}


	l = buf + n - p;
	if (l > 0) {
		memcpy(line, p, n);
		linep = line + l;
	}
}
