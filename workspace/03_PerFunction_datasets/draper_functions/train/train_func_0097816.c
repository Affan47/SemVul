Sync(void) {
	switch (bank_mode) {
	case 0x00:
	case 0x10:
		setprg16(0x8000, large_bank | prg_bank);
		setprg16(0xC000, large_bank | 7);
		break;
	case 0x20:
		setprg32(0x8000, (large_bank | prg_bank) >> 1);
		break;
	case 0x30:
		setprg16(0x8000, large_bank | prg_bank);
		setprg16(0xC000, large_bank | prg_bank);
		break;
	}
	setmirror(mirroring);
	if (!is_large_banks)
		setchr8(chr_bank);
}
