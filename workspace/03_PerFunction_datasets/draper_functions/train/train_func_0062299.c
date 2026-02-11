is_binary(unsigned char *s, size_t n)
{
	size_t i;
	for (i = 0; i < n; i++)
		if (s[i] < 0x07 || (s[i] >= 0x0e && s[i] < 0x20)) return 1;
	return 0;
}
