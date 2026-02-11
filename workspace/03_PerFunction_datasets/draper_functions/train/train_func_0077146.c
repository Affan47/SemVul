CDB___os_strdup(str, storep)
	const char *str;
	void *storep;
{
	size_t size;
	int ret;
	void *p;

	*(void **)storep = NULL;

	size = strlen(str) + 1;
	if ((ret = CDB___os_malloc(size, NULL, &p)) != 0)
		return (ret);

	memcpy(p, str, size);

	*(void **)storep = p;
	return (0);
}
