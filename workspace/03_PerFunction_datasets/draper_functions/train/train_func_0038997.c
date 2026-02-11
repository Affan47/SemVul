bucketsForSize( int size )
{
	int base = 4, bits = 2;

	for (;;) {
		int prime = base + prime_deltas[bits];
		if (prime >= size)
			return prime;
		base <<= 1;
		bits++;
	}
}
