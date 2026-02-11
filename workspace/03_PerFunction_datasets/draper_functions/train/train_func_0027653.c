pstrdup(pool p, const char *src)
{
	char *ret;

	if (src == NULL)
		return NULL;

	ret = pmalloc(p, strlen(src) + 1);
	strcpy(ret, src);

	return ret;
}
