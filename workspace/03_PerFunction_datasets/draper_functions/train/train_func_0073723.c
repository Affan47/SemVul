_strlen(const char *str, size_t max)
{
	const char *s = str;
	size_t len = 0;

	while (*s++ && len < max)
		len++;

	return len;
}
