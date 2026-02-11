_b64_chr(uint8_t i)
{
	i = i & 63;
	if (i < 26) return 'A' + (i - 0);
	if (i < 52) return 'a' + (i - 26);
	if (i < 62) return '0' + (i - 52);
	if (i == 62) return '+';
	if (i == 63) return '/';
	return '?';
}
