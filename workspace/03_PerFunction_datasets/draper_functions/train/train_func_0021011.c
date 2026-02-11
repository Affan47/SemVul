lookup_bh_lru(struct block_device *bdev, sector_t block, unsigned size)
{
	struct buffer_head *ret = NULL;
	unsigned int i;

	check_irqs_on();
	bh_lru_lock();
	for (i = 0; i < BH_LRU_SIZE; i++) {
		struct buffer_head *bh = __this_cpu_read(bh_lrus.bhs[i]);

		if (bh && bh->b_blocknr == block && bh->b_bdev == bdev &&
		    bh->b_size == size) {
			if (i) {
				while (i) {
					__this_cpu_write(bh_lrus.bhs[i],
						__this_cpu_read(bh_lrus.bhs[i - 1]));
					i--;
				}
				__this_cpu_write(bh_lrus.bhs[0], bh);
			}
			get_bh(bh);
			ret = bh;
			break;
		}
	}
	bh_lru_unlock();
	return ret;
}
