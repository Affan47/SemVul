fast_strtoul_10(char **endptr)
{
	unsigned char c;
	char *str = *endptr;
	unsigned long n = *str - '0';


	while ((c = *++str) > ' ')
		n = n*10 + (c - '0');

	*endptr = str + 1;
	return n;
}
