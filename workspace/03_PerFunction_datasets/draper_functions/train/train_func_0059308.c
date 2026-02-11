copy_backup_region(void)
{
	if (backup_dest)
		memcpy((void *)backup_dest, (void *)backup_src, backup_sz);

	return 0;
}
