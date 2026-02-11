BuildWRAMSizeTable(void) {
	int x;
	for (x = 0; x < 8; x++) {
		switch (MMC5WRAMsize) {
		case 0: MMC5WRAMIndex[x] = 255; break;
		case 1: MMC5WRAMIndex[x] = (x > 3) ? 255 : 0; break;
		case 2: MMC5WRAMIndex[x] = (x & 4) >> 2; break;
		case 4: MMC5WRAMIndex[x] = (x > 3) ? 255 : (x & 3); break;
		case 8: MMC5WRAMIndex[x] = x; break;
		}
	}
}
