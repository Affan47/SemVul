cdrom_read_tocentry(ide_drive_t *drive, int trackno, int msf_flag,
				int format, char *buf, int buflen,
				struct request_sense *sense)
{
	unsigned char cmd[BLK_MAX_CDB];

	ide_debug_log(IDE_DBG_FUNC, "enter");

	memset(cmd, 0, BLK_MAX_CDB);

	cmd[0] = GPCMD_READ_TOC_PMA_ATIP;
	cmd[6] = trackno;
	cmd[7] = (buflen >> 8);
	cmd[8] = (buflen & 0xff);
	cmd[9] = (format << 6);

	if (msf_flag)
		cmd[1] = 2;

	return ide_cd_queue_pc(drive, cmd, 0, buf, &buflen, sense, 0, REQ_QUIET);
}
