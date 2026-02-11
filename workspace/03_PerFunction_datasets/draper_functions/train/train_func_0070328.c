BMCT2271PW(uint32 A, uint8 V) {
	uint32 va = V & 0x3F;
	if (EXPREGS[0] & 0x20) {
		va &= 0x1F;
		va |= 0x40;
		va |= (EXPREGS[0] & 0x10) << 1;
	} else {
		va &= 0x0F;
		va |= (EXPREGS[0] & 0x18) << 1;
	}
	switch (EXPREGS[0] & 3) {
	case 0x00: setprg8(A, va); break;
	case 0x02:
	{
		va = (va & 0xFD) | ((EXPREGS[0] & 4) >> 1);
		if (A < 0xC000) {
			setprg16(0x8000, va >> 1);
			setprg16(0xC000, va >> 1);
		}
		break;
	}
	case 0x01:
	case 0x03: if (A < 0xC000) setprg32(0x8000, va >> 2); break;
	}
}
