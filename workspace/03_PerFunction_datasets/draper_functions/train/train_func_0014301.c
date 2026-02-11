MMC1MIRROR(void) {
	if (!is171)
		switch (DRegs[0] & 3) {
		case 2: setmirror(MI_V); break;
		case 3: setmirror(MI_H); break;
		case 0: setmirror(MI_0); break;
		case 1: setmirror(MI_1); break;
		}
}
