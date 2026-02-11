split_nicks(const char *cmd, char **pre, char **nicks, char **post, int arg)
{
	char *p;

	*pre = g_strdup(cmd);
	*post = *nicks = NULL;
	for (p = *pre; *p != '\0'; p++) {
		if (*p != ' ')
			continue;

		if (arg == 1) {

			*p++ = '\0';
			while (*p == ' ') p++;
			*post = p;
			break;
		}


		while (p[1] == ' ') p++;
		if (--arg == 1) {
			*p = '\0';
			*nicks = p+1;
		}
	}

	return *pre;
}
