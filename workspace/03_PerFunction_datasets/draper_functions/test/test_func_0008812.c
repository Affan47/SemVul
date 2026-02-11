BUF_strlcat(char *dst, const char *src, size_t size)
	{
	size_t l = 0;
	for(; size > 0 && *dst; size--, dst++)
		l++;
	return l + BUF_strlcpy(dst, src, size);
	}
