nyb(int c)
{
	static const char xdigits[]="0123456789ABCDEFabcdef";

	char *p=strchr(xdigits, c);

	if (!p)
		return (0);

	c= p-xdigits;

	if (c >= 16)
		c -= 6;
	return (c);
}
