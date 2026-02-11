create_str_list(char *cslist) {
	int i, n;
	char *p, *str;
	char **list = NULL;

	if (! cslist) {
		return NULL;
	}

	str = strdup(cslist);
	n = 1;
	p = str;
	while (*p != '\0') {
		if (*p == ',') {
			n++;
		}
		p++;
	}


	list = (char **) calloc((n+1)*sizeof(char *), 1);

	p = strtok(str, ",");
	i = 0;
	while (p && i < n) {
		list[i++] = strdup(p);
		p = strtok(NULL, ",");
	}
	free(str);

	return list;
}
