BandaiSync(void) {
	if (is153) {
		int base = (reg[0] & 1) << 4;
		setchr8(0);
		setprg16(0x8000, (reg[8] & 0x0F) | base);
		setprg16(0xC000, 0x0F | base);
	} else {
		int i;
		for (i = 0; i < 8; i++) setchr1(i << 10, reg[i]);
		setprg16(0x8000, reg[8]);
		setprg16(0xC000, ~0);
	}
	switch (reg[9] & 3) {
	case 0: setmirror(MI_V); break;
	case 1: setmirror(MI_H); break;
	case 2: setmirror(MI_0); break;
	case 3: setmirror(MI_1); break;
	}
}
