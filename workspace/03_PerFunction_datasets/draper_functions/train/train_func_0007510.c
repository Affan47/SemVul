encode_length(unsigned long val)
{
	unsigned int bits = afls(val);

	if (bits <= 5)
		return 1;

	return 2 + (bits - 5) / 7;
}
