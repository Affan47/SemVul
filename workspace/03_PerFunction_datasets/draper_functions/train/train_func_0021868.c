getcmdline(char **linep, size_t *lenp, FILE *in)
{
	size_t cc;
	char *cp;

	if ((cc = getline(linep, lenp, in)) < 0)
		return cc;
	++cmdlineno;

	cp = strchr(*linep, '#');
	if (cp)
		*cp = '\0';

	while ((cp = strstr(*linep, "\\\n")) != NULL) {
		char *line1 = NULL;
		size_t len1 = 0;
		size_t cc1;

		if ((cc1 = getline(&line1, &len1, in)) < 0) {
			fprintf(stderr, "Missing continuation line\n");
			return cc1;
		}

		++cmdlineno;
		*cp = 0;

		cp = strchr(line1, '#');
		if (cp)
			*cp = '\0';

		*linep = realloc(*linep, strlen(*linep) + strlen(line1) + 1);
		if (!*linep) {
			fprintf(stderr, "Out of memory\n");
			return -1;
		}
		cc += cc1 - 2;
		strcat(*linep, line1);
		free(line1);
	}
	return cc;
}
