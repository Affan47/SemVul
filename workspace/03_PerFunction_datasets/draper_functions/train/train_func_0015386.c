_fetch_string(char **ptr, char **src, const int delimiter)
{
	int ret = 0;
	char *p;
	size_t len;

	if ((p = strchr(*src, delimiter)))
		*p = 0;

	if ((*ptr = dm_strdup(*src))) {
		if ((len = strlen(*ptr)))
			*src += len;
		else {
			dm_free(*ptr);
			*ptr = NULL;
		}

		(*src)++;
		ret = 1;
	}

	if (p)
		*p = delimiter;

	return ret;
}
