Sync(void) {
	if (mode & 2) {
		setprg8(0x6000, ((bank & 7) << 2) | 0x23);
		setprg16(0x8000, (bank << 1) | 0);
		setprg16(0xC000, (bank << 1) | 1);
	} else {
		setprg8(0x6000, ((bank & 4) << 2) | 0x2F);
		setprg16(0x8000, (bank << 1) | (mode >> 4));
		setprg16(0xC000, ((bank & 0xC) << 1) | 7);
	}
	if (mode == 0x12)
		setmirror(MI_H);
	else
		setmirror(MI_V);
	setchr8(0);
}
