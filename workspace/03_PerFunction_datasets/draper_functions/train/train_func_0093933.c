mcf_wrap(struct cli *cli, const char *text)
{
	const char *p, *q;


	for (p = text; *p != '\0'; ) {
		q = strchr(p, '\n');
		if (q == NULL)
			q = strchr(p, '\0');
		if (q > p + WIDTH - margin) {
			q = p + WIDTH - margin;
			while (q > p && *q != ' ')
				q--;
			AN(q);
		}
		VCLI_Out(cli, "%*s %.*s\n", margin, "", (int)(q - p), p);
		p = q;
		if (*p == ' ' || *p == '\n')
			p++;
	}
}
