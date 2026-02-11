ide_cdrom_get_mcn(struct cdrom_device_info *cdi,
		      struct cdrom_mcn *mcn_info)
{
	ide_drive_t *drive = cdi->handle;
	int stat, mcnlen;
	char buf[24];
	unsigned char cmd[BLK_MAX_CDB];
	unsigned len = sizeof(buf);

	memset(cmd, 0, BLK_MAX_CDB);

	cmd[0] = GPCMD_READ_SUBCHANNEL;
	cmd[1] = 2;
	cmd[2] = 0x40;
	cmd[3] = 2;
	cmd[8] = len;

	stat = ide_cd_queue_pc(drive, cmd, 0, buf, &len, NULL, 0, 0);
	if (stat)
		return stat;

	mcnlen = sizeof(mcn_info->medium_catalog_number) - 1;
	memcpy(mcn_info->medium_catalog_number, buf + 9, mcnlen);
	mcn_info->medium_catalog_number[mcnlen] = '\0';

	return 0;
}
