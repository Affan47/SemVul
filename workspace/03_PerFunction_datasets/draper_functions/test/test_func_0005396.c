f_sync (
	FIL *fp
)
{
	FRESULT res;
	DWORD tim;
	BYTE *dir;


	res = validate(fp->fs, fp->id);
	if (res == FR_OK) {
		if (fp->flag & FA__WRITTEN) {
#if !_FS_TINY
			if (fp->flag & FA__DIRTY) {
				if (disk_write(fp->fs->drv, fp->buf, fp->dsect, 1) != RES_OK)
					LEAVE_FF(fp->fs, FR_DISK_ERR);
				fp->flag &= ~FA__DIRTY;
			}
#endif

			res = move_window(fp->fs, fp->dir_sect);
			if (res == FR_OK) {
				dir = fp->dir_ptr;
				dir[DIR_Attr] |= AM_ARC;
				ST_DWORD(dir+DIR_FileSize, fp->fsize);
				ST_CLUST(dir, fp->sclust);
				tim = get_fattime();
				ST_DWORD(dir+DIR_WrtTime, tim);
				fp->flag &= ~FA__WRITTEN;
				fp->fs->wflag = 1;
				res = sync(fp->fs);
			}
		}
	}

	LEAVE_FF(fp->fs, res);
}
