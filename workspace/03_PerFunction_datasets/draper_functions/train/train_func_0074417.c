Sync(void) {
	if (prg_reg & 0x80)
		setprg32(0x8000, prg_reg >> 6);
	else{
		setprg16(0x8000, (prg_reg >> 5) & 3);
		setprg16(0xC000, (prg_reg >> 5) & 3);
	}
	setmirror((prg_reg & 8) >> 3);
	setchr8((chr_reg & 3) | (prg_reg & 7) | ((prg_reg & 0x10) >> 1));
}
