validate (
	FATFS *fs,
	WORD id
)
{
	if (!fs || !fs->fs_type || fs->id != id)
		return FR_INVALID_OBJECT;

	ENTER_FF(fs);

	if (disk_status(fs->drv) & STA_NOINIT)
		return FR_NOT_READY;

	return FR_OK;
}
