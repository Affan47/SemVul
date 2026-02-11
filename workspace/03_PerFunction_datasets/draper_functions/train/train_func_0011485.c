parse_push(struct strbuf *buf)
{
	char **specs = NULL;
	int alloc_spec = 0, nr_spec = 0, i;

	do {
		if (!prefixcmp(buf->buf, "push ")) {
			ALLOC_GROW(specs, nr_spec + 1, alloc_spec);
			specs[nr_spec++] = xstrdup(buf->buf + 5);
		}
		else
			die("http transport does not support %s", buf->buf);

		strbuf_reset(buf);
		if (strbuf_getline(buf, stdin, '\n') == EOF)
			return;
		if (!*buf->buf)
			break;
	} while (1);

	if (push(nr_spec, specs))
		exit(128);
	for (i = 0; i < nr_spec; i++)
		free(specs[i]);
	free(specs);

	printf("\n");
	fflush(stdout);
}
