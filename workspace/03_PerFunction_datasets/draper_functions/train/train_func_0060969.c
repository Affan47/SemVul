list_to_types(const char *list, int *flag)
{
	int i;
	const char *p = list;
	char **res = NULL;

	if (p && strncmp(p, "no", 2) == 0) {
		*flag = BLKID_FLTR_NOTIN;
		p += 2;
	}
	if (!p || !*p) {
		fprintf(stderr, "error: -u <list> argument is empty\n");
		goto err;
	}
	for (i = 1; p && (p = strchr(p, ',')); i++, p++);

	res = calloc(i + 1, sizeof(char *));
	if (!res)
		goto err_mem;
	p = *flag & BLKID_FLTR_NOTIN ? list + 2 : list;
	i = 0;

	while(p) {
		const char *word = p;
		p = strchr(p, ',');
		res[i] = p ? strndup(word, p - word) : strdup(word);
		if (!res[i++])
			goto err_mem;
		if (p)
			p++;
	}
	res[i] = NULL;
	return res;
err_mem:
	fprintf(stderr, "out of memory\n");
err:
	*flag = 0;
	free(res);
	exit(4);
}
