au_strtol (const unsigned char *str, unsigned char **end)
{
	char *send;
	long res = strtol ((const char *)str, &send, 10);
	if (end) *end = (unsigned char *)send;
	return res;
}
