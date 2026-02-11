encode_float(u64 value)
{
	unsigned exp = 190;
	unsigned u;

	if (value == 0)
		return 0;
	while ((s64)value > 0) {
		value <<= 1;
		exp--;
	}
	u = (u32)(value >> 40) & 0x7fffffu;
	return u | (exp << 23);
}
