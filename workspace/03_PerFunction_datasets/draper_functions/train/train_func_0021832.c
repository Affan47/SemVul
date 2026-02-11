sync (
	FATFS *fs
)
{
	FRESULT res;


	res = move_window(fs, 0);
	if (res == FR_OK) {

		if (fs->fs_type == FS_FAT32 && fs->fsi_flag) {
			fs->winsect = 0;

			mem_set(fs->win, 0, 512);
			ST_WORD(fs->win+BS_55AA, 0xAA55);
			ST_DWORD(fs->win+FSI_LeadSig, 0x41615252);
			ST_DWORD(fs->win+FSI_StrucSig, 0x61417272);
			ST_DWORD(fs->win+FSI_Free_Count, fs->free_clust);
			ST_DWORD(fs->win+FSI_Nxt_Free, fs->last_clust);

			disk_write(fs->drv, fs->win, fs->fsi_sector, 1);
			fs->fsi_flag = 0;
		}

		if (disk_ioctl(fs->drv, CTRL_SYNC, (void*)0) != RES_OK)
			res = FR_DISK_ERR;
	}

	return res;
}
