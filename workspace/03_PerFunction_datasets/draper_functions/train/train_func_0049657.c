array_make_count(const char *string, char sep, int *arrcnt) {
	const char *p;
	char **result = NULL;
	int items = 0;

	for (p = string; *p; p++) {
		const char *q;
		char *token;
		int len;

		for (q = p, len = 0; (*q && *q != sep); q++, len++);


		token = xstrndup(p, len);

		xstrtr(token, '\x8', '\n');
		p = q;

		result = xrealloc(result, (items + 2) * sizeof(char*));
		result[items] = token;
		result[++items] = NULL;

		if (!*p)
			break;
	}
	*arrcnt = items;

	return result;
}
