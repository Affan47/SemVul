probe_minix(blkid_probe pr, const struct blkid_idmag *mag)
{
	unsigned char *ext;
	int version;


	switch(mag->magic[1]) {
	case '\023':
		version = 1;
		break;
	case '\044':
		version = 2;
		break;
	case '\115':
		version = 3;
		break;
	default:
		return -1;
		break;
	}

	if (version <= 2) {
		struct minix_super_block *sb;
		uint32_t zones;

		sb = blkid_probe_get_sb(pr, mag, struct minix_super_block);
		if (!sb || sb->s_imap_blocks == 0 || sb->s_zmap_blocks == 0)
			return -1;

		zones = version == 2 ? sb->s_zones : sb->s_nzones;


		if (sb->s_imap_blocks * MINIX_BLOCK_SIZE * 8 < sb->s_ninodes + 1)
			return -1;
		if (sb->s_zmap_blocks * MINIX_BLOCK_SIZE * 8 < zones - sb->s_firstdatazone + 1)
			return -1;

	} else if (version == 3) {
		struct minix3_super_block *sb;

		sb = blkid_probe_get_sb(pr, mag, struct minix3_super_block);
		if (!sb || sb->s_imap_blocks == 0 || sb->s_zmap_blocks == 0)
			return -1;

	}


	ext = blkid_probe_get_buffer(pr, 0x400 + 0x38, 2);
	if (ext && memcmp(ext, "\123\357", 2) == 0)
		return -1;

	blkid_probe_sprintf_version(pr, "%d", version);
	return 0;
}
