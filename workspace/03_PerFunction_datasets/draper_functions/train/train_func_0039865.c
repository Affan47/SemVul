keyword_fits(size_t used, size_t max, const char *key, const char *value)
{
	size_t	vsize = 0;

	if(key != NULL && value != NULL)
		vsize += 1 + strlen(key) + 1 + 1 + strlen(value) + 1;

	return max - 1 - used >= vsize;
}
