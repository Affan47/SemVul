ujfs_get_superblk(FILE *fp, struct superblock *sb, int32_t is_primary)
{
	int rc;
	char buf[SIZE_OF_SUPER];
	struct superblock *sblk = (struct superblock *) buf;

	rc = ujfs_rw_diskblocks(fp, (is_primary ? SUPER1_OFF : SUPER2_OFF),
				SIZE_OF_SUPER, sblk, GET);

	ujfs_swap_superblock(sblk);

	if (rc != 0)
		return rc;

	memcpy(sb, sblk, sizeof (*sb));
	return 0;
}
