path_open(const char *path, const char *filename, char **fullp)
{
	if (LocalFileName(filename) && path != NULL) {
#ifdef PATH_DELIMITER
		int	len;
		char	*fullname;
		FILE	*f;
		const	char	*p_next;

		len = strlen(filename);
		for (;;) {
			p_next = strchr(path, PATH_DELIMITER);
			if (p_next == NULL)
				p_next = path + strlen(path);
			fullname = concat(path, p_next - path, filename);
			if ((f = fopen(fullname, "r")) != NULL) {
				*fullp = fullname;
				return f;
			}
			free(fullname);
			if (*p_next == '\0')
				break;
			path = p_next + 1;
		}
#endif
		return NULL;
	}
	else {
		*fullp = strdup(filename);
		return fopen(*fullp, "r");
	}
}
