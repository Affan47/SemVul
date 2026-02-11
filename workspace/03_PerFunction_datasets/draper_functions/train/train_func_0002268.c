shift_bits(unsigned int value,
				      unsigned int shift_from,
				      unsigned int shift_to,
				      unsigned int mask)
{
	if (shift_from < shift_to)
		return (value << (shift_to - shift_from)) & mask;
	else
		return (value >> (shift_from - shift_to)) & mask;
}
