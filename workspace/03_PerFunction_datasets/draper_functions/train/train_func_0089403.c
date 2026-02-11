minix_image(const void *buf, unsigned long long *bytes)
{
	const struct minix_super_block *sb =
	    (const struct minix_super_block *)buf;

	if (sb->s_magic == MINIX_SUPER_MAGIC ||
	    sb->s_magic == MINIX_SUPER_MAGIC2) {
		*bytes = (unsigned long long)sb->s_nzones
		    << (sb->s_log_zone_size + 10);
		return 1;
	}
	return 0;
}
