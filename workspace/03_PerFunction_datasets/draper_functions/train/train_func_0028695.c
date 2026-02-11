revert(void *src, void *dst, size_t t)
{
	int i;
	for (i = 0 ; i < t ; i++)
		((char *)dst)[i] = ((char *)src)[t - i - 1];
}
