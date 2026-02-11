count_run(unsigned long **addr, int nbits,
		int addrlen, int bit, int max)
{
	int count = 0;
	int x;

	for (; addrlen > 0; addrlen--, addr++) {
		x = find_next_bit(*addr, nbits, bit);
		count += x - bit;

		if (x < nbits || count > max)
			return min(count, max);

		bit = 0;
	}
	return min(count, max);
}
