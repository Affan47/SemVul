f_readdir (
	DIR *dj,
	FILINFO *fno
)
{
	FRESULT res;
	DEF_NAMEBUF;


	res = validate(dj->fs, dj->id);
	if (res == FR_OK) {
		if (!fno) {
			res = dir_sdi(dj, 0);
		} else {
			INIT_BUF(*dj);
			res = dir_read(dj);
			if (res == FR_NO_FILE) {
				dj->sect = 0;
				res = FR_OK;
			}
			if (res == FR_OK) {
				get_fileinfo(dj, fno);
				res = dir_next(dj, 0);
				if (res == FR_NO_FILE) {
					dj->sect = 0;
					res = FR_OK;
				}
			}
			FREE_BUF();
		}
	}

	LEAVE_FF(dj->fs, res);
}
