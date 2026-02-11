bdev_erase(struct super_block *sb, loff_t to, size_t len,
		int ensure_write)
{
	struct logfs_super *super = logfs_super(sb);

	BUG_ON(to & (PAGE_SIZE - 1));
	BUG_ON(len & (PAGE_SIZE - 1));

	if (super->s_flags & LOGFS_SB_FLAG_RO)
		return -EROFS;

	if (ensure_write) {


		do_erase(sb, to, to >> PAGE_SHIFT, len >> PAGE_SHIFT);
	}

	return 0;
}
