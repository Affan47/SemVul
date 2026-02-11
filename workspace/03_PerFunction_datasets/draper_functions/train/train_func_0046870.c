write_cached_data (struct mtdblk_dev *mtdblk)
{
	struct mtd_info *mtd = mtdblk->mbd.mtd;
	int ret;

	if (mtdblk->cache_state != STATE_DIRTY)
		return 0;

	pr_debug("mtdblock: writing cached data for \"%s\" "
			"at 0x%lx, size 0x%x\n", mtd->name,
			mtdblk->cache_offset, mtdblk->cache_size);

	ret = erase_write (mtd, mtdblk->cache_offset,
			   mtdblk->cache_size, mtdblk->cache_data);
	if (ret)
		return ret;


	mtdblk->cache_state = STATE_EMPTY;
	return 0;
}
