set_bit(unsigned char *array, unsigned int index, unsigned int bit) {
	unsigned int shift, mask;

	shift = 7 - (index % 8);
	mask = 1 << shift;

	if (bit != 0)
		array[index / 8] |= mask;
	else
		array[index / 8] &= (~mask & 0xFF);
}
