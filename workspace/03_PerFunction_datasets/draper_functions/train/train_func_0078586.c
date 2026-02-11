readdata(char *packet, char **src, char *dst, size_t len)
{
	if (len < 0)
		return 0;

	memcpy(dst, *src, len);

	(*src) += len;

	return len;
}
