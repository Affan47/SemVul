parity(u8 v)
{
	int x = 0;
	int i;

	for (i = 0; i < 8; i++) {
		x ^= (v & 1);
		v >>= 1;
	}

	return x;
}
