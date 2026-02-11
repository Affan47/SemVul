gfarm_pgsql_make_conninfo(const char **varnames, char **varvalues, int n,
	char *others)
{
	int i;
	size_t length = 0;
	char *v, *conninfo, *p;


	for (i = 0; i < n; i++) {
		if ((v = varvalues[i]) != NULL) {
			if (i > 1)
				length++;
			length += strlen(varnames[i]) + 3;
			for (; *v != '\0'; v++) {
				if (*v == '\'' || *v == '\\')
					++length;
				++length;
			}
		}
	}
	if (others != NULL) {
		if (length > 0)
			++length;
		length += strlen(others);
	}
	++length;

	GFARM_MALLOC_ARRAY(conninfo, length);
	if (conninfo == NULL) {
		gflog_debug(GFARM_MSG_1002144,
			"allocation of 'conninfo' failed");
		return (NULL);
	}

	p = conninfo;
	for (i = 0; i < n; i++) {
		if ((v = varvalues[i]) != NULL) {
			if (i > 1)
				*p++ = ' ';
			p += sprintf(p, "%s='", varnames[i]);
			for (; *v != '\0'; v++) {
				if (*v == '\'' || *v == '\\')
					*p++ = '\\';
				*p++ = *v;
			}
			*p++ = '\'';
		}
	}
	if (others != NULL) {
		if (p > conninfo)
			*p++ = ' ';
		p += sprintf(p, "%s", others);
	}
	*p++ = '\0';
	return (conninfo);
}
