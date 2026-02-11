dir_read (
	DIR *dj
)
{
	FRESULT res;
	BYTE c, *dir;
#if _USE_LFN
	BYTE a, ord = 0xFF, sum = 0xFF;
#endif

	res = FR_NO_FILE;
	while (dj->sect) {
		res = move_window(dj->fs, dj->sect);
		if (res != FR_OK) break;
		dir = dj->dir;
		c = dir[DIR_Name];
		if (c == 0) { res = FR_NO_FILE; break; }
#if _USE_LFN
		a = dir[DIR_Attr] & AM_MASK;
		if (c == DDE || (!_FS_RPATH && c == '.') || ((a & AM_VOL) && a != AM_LFN)) {
			ord = 0xFF;
		} else {
			if (a == AM_LFN) {
				if (c & LLE) {
					sum = dir[LDIR_Chksum];
					c &= ~LLE; ord = c;
					dj->lfn_idx = dj->index;
				}

				ord = (c == ord && sum == dir[LDIR_Chksum] && pick_lfn(dj->lfn, dir)) ? ord - 1 : 0xFF;
			} else {
				if (ord || sum != sum_sfn(dir))
					dj->lfn_idx = 0xFFFF;
				break;
			}
		}
#else
		if (c != DDE && (_FS_RPATH || c != '.') && !(dir[DIR_Attr] & AM_VOL))
			break;
#endif
		res = dir_next(dj, 0);
		if (res != FR_OK) break;
	}

	if (res != FR_OK) dj->sect = 0;

	return res;
}
