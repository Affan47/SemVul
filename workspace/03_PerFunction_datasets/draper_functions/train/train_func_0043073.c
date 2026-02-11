saa711x_decode_wss(u8 *p)
{
	static const int wss_bits[8] = {
		0, 0, 0, 1, 0, 1, 1, 1
	};
	unsigned char parity;
	int wss = 0;
	int i;

	for (i = 0; i < 16; i++) {
		int b1 = wss_bits[p[i] & 7];
		int b2 = wss_bits[(p[i] >> 3) & 7];

		if (b1 == b2)
			return -1;
		wss |= b2 << i;
	}
	parity = wss & 15;
	parity ^= parity >> 2;
	parity ^= parity >> 1;

	if (!(parity & 1))
		return -1;

	return wss;
}
