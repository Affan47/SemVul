ostrndup(const char *str, size_t n)
{
	size_t len;
	char *res;

	if (NULL == str)
		return NULL;

	len = clamp_strlen(str, n);
	res = omalloc_allocate(1 + len, 1, OMALLOC_RW, str);
	res[len] = '\0';

	return res;
}
