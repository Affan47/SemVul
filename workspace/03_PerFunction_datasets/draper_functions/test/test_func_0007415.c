mtdblock_release(struct mtd_blktrans_dev *mbd)
{
	struct mtdblk_dev *mtdblk = container_of(mbd, struct mtdblk_dev, mbd);

	pr_debug("mtdblock_release\n");

	mutex_lock(&mtdblk->cache_mutex);
	write_cached_data(mtdblk);
	mutex_unlock(&mtdblk->cache_mutex);

	if (!--mtdblk->count) {


		if (mbd->file_mode & FMODE_WRITE)
			mtd_sync(mbd->mtd);
		vfree(mtdblk->cache_data);
	}

	pr_debug("ok\n");
}
