t_getenv(const char *name) {
	char	*n;
	char	**p;
	size_t	len;

	n = NULL;
	if (name && *name) {

		p = &T_env[0];
		len = strlen(name);

		while (*p != NULL) {
			if (strncmp(*p, name, len) == 0) {
				if ( *(*p + len) == '=') {
					n = *p + len + 1;
					break;
				}
			}
			++p;
		}
	}
	return(n);
}
