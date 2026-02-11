zfile_fopen_archive_data (struct znode *parent, struct zfile *zf, int flags)
{
	struct zvolume *zv = NULL;
	uae_u8 header[32];

	memset (header, 0, sizeof (header));
	zfile_fread (header, sizeof (header), 1, zf);
	zfile_fseek (zf, 0, SEEK_SET);
	if (flags & ZFD_ARCHIVE) {
#ifdef A_ZIP
		if (header[0] == 'P' && header[1] == 'K')
			zv = archive_directory_zip (zf);
#endif
#ifdef A_RAR
		if (header[0] == 'R' && header[1] == 'a' && header[2] == 'r' && header[3] == '!')
			zv = archive_directory_rar (zf);
#endif
#ifdef A_LZX
		if (header[0] == 'L' && header[1] == 'Z' && header[2] == 'X')
			zv = archive_directory_lzx (zf);
#endif
#ifdef A_LHA
		if (header[2] == '-' && header[3] == 'l' && header[4] == 'h' && header[6] == '-')
			zv = archive_directory_lha (zf);
#endif
	}
	if (flags & ZFD_ADF) {
		if (header[0] == 'D' && header[1] == 'O' && header[2] == 'S' && (header[3] >= 0 && header[3] <= 7))
			zv = archive_directory_adf (parent, zf);
	}
	if (flags & ZFD_HD) {
		if (header[0] == 'R' && header[1] == 'D' && header[2] == 'S' && header[3] == 'K')
			zv = archive_directory_rdb (zf);
		if (isfat (header))
			zv = archive_directory_fat (zf);
	}
	return zv;
}
