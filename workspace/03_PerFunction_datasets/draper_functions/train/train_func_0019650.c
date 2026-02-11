logfs_mtd_read(struct super_block *sb, loff_t ofs, size_t len,
			void *buf)
{
	struct mtd_info *mtd = logfs_super(sb)->s_mtd;
	size_t retlen;
	int ret;

	ret = mtd_read(mtd, ofs, len, &retlen, buf);
	BUG_ON(ret == -EINVAL);
	if (ret)
		return ret;


	if (retlen != len)
		return -EIO;

	return 0;
}
