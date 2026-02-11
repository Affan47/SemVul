nearest_power(unsigned long num)
{
	unsigned long n = BITSET_DEFAULT_SIZE;

	while (n < num) {
		n <<= 1;
		if (n == 0) {
			return num;
		}
	}
	return n;
}
