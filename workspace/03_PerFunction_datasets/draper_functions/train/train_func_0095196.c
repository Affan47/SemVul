get_fat (
	FATFS *fs,
	DWORD clst
) {
	UINT wc, bc;
	BYTE *p;


	if (clst < 2 || clst >= fs->n_fatent) {
		return 1;
	}

	switch (fs->fs_type) {
		case FS_FAT12 :
			bc = (UINT)clst;
			bc += bc / 2;
			if (move_window(fs, fs->fatbase + (bc / SS(fs)))) {
				break;
			}
			wc = fs->win[bc % SS(fs)];
			bc++;
			if (move_window(fs, fs->fatbase + (bc / SS(fs)))) {
				break;
			}
			wc |= fs->win[bc % SS(fs)] << 8;
			return (clst & 1) ? (wc >> 4) : (wc & 0xFFF);

		case FS_FAT16 :
			if (move_window(fs, fs->fatbase + (clst / (SS(fs) / 2)))) {
				break;
			}
			p = &fs->win[clst * 2 % SS(fs)];
			return LD_WORD(p);

		case FS_FAT32 :
			if (move_window(fs, fs->fatbase + (clst / (SS(fs) / 4)))) {
				break;
			}
			p = &fs->win[clst * 4 % SS(fs)];
			return LD_DWORD(p) & 0x0FFFFFFF;
	}

	return 0xFFFFFFFF;
}
