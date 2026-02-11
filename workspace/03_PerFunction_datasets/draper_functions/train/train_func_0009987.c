convert_binary(const char *s)
{
	unsigned long long v = 0;

	for (; *s; s++) {
		v <<= 1;
		if (*s == '1')
			v |= 1;
	}
	return v;
}
