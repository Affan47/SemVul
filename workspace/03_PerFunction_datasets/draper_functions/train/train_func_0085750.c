makeppulut(void) {
	int x;
	int y;
	int cc, xo, pixel;


	for (x = 0; x < 256; x++) {
		ppulut1[x] = 0;

		for (y = 0; y < 8; y++) {
			ppulut1[x] |= ((x >> (7 - y)) & 1) << (y * 4);
		}

		ppulut2[x] = ppulut1[x] << 1;
	}

	for (cc = 0; cc < 16; cc++) {
		for (xo = 0; xo < 8; xo++) {
			ppulut3[ xo | (cc << 3) ] = 0;

			for (pixel = 0; pixel < 8; pixel++) {
				int shiftr;
				shiftr = (pixel + xo) / 8;
				shiftr *= 2;
				ppulut3[ xo | (cc << 3) ] |= ((cc >> shiftr) & 3) << (2 + pixel * 4);
			}
		}
	}
}
