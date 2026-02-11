der_get_unsigned(const unsigned char *p, size_t len,
		 unsigned *ret, size_t *size)
{
	unsigned val = 0;
	size_t oldlen = len;

	while (len--)
		val = val * 256 + *p++;
	*ret = val;
	if (size)
		*size = oldlen;
	return (0);
}
