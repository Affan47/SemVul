MMC1PRG(void) {
	uint8 offs = DRegs[1] & 0x10;
	if (MMC1PRGHook16) {
		switch (DRegs[0] & 0xC) {
		case 0xC:
			MMC1PRGHook16(0x8000, (DRegs[3] + offs));
			MMC1PRGHook16(0xC000, 0xF + offs);
			break;
		case 0x8:
			MMC1PRGHook16(0xC000, (DRegs[3] + offs));
			MMC1PRGHook16(0x8000, offs);
			break;
		case 0x0:
		case 0x4:
			MMC1PRGHook16(0x8000, ((DRegs[3] & ~1) + offs));
			MMC1PRGHook16(0xc000, ((DRegs[3] & ~1) + offs + 1));
			break;
		}
	} else {
		switch (DRegs[0] & 0xC) {
		case 0xC:
			setprg16(0x8000, (DRegs[3] + offs));
			setprg16(0xC000, 0xF + offs);
			break;
		case 0x8:
			setprg16(0xC000, (DRegs[3] + offs));
			setprg16(0x8000, offs);
			break;
		case 0x0:
		case 0x4:
			setprg16(0x8000, ((DRegs[3] & ~1) + offs));
			setprg16(0xc000, ((DRegs[3] & ~1) + offs + 1));
			break;
		}
	}
}
