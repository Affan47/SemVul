FFCEUX_PPURead_Default(uint32 A) {
	uint32 tmp = A;

	if (PPU_hook) PPU_hook(A);

	if (tmp < 0x2000) {
		return VPage[tmp >> 10][tmp];
	} else if (tmp < 0x3F00) {
		return vnapage[(tmp >> 10) & 0x3][tmp & 0x3FF];
	} else {
		uint8 ret;
		if (!(tmp & 3)) {
			if (!(tmp & 0xC))
				ret = PALRAM[0x00];
			else
				ret = UPALRAM[((tmp & 0xC) >> 2) - 1];
		} else
			ret = PALRAM[tmp & 0x1F];

		if (GRAYSCALE)
			ret &= 0x30;
		return ret;
	}
}
