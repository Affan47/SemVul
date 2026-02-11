print_desc(const char *pre, const char *text)
{
	const char *p, *q;

	for (p = text, q = strchr(p, '\n'); q; p = q+1, q = strchr(p, '\n'))
		printf("%s%.*s\n", pre, (int)(q-p), p);

	if (*p != '\0')
		printf("%s%s\n", pre, p);
}
