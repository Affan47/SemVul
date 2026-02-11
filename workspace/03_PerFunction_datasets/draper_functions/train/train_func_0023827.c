get_uint_range(char *str, int base, unsigned long long max)
{
	unsigned long long v;
	char *endp;

	if (!str)
		exit_bad_args();
	errno = 0;
	v = strtoull(str, &endp, base);
	if ( errno || *endp || v > max)
		exit_bad_args();
	return v;
}
