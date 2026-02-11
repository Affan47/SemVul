check_fs (
	FATFS *fs,
	DWORD sect
) {
	if (disk_read(fs->drv, fs->win, sect, 1) != RES_OK) {
		return 3;
	}
	if (LD_WORD(&fs->win[BS_55AA]) != 0xAA55) {
		return 2;
	}

	if ((LD_DWORD(&fs->win[BS_FilSysType]) & 0xFFFFFF) == 0x544146) {
		return 0;
	}
	if ((LD_DWORD(&fs->win[BS_FilSysType32]) & 0xFFFFFF) == 0x544146) {
		return 0;
	}

	return 1;
}
