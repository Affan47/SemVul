zram_bio_discard(struct zram *zram, u32 index,
			     int offset, struct bio *bio)
{
	size_t n = bio->bi_iter.bi_size;
	struct zram_meta *meta = zram->meta;


	if (offset) {
		if (n <= (PAGE_SIZE - offset))
			return;

		n -= (PAGE_SIZE - offset);
		index++;
	}

	while (n >= PAGE_SIZE) {
		bit_spin_lock(ZRAM_ACCESS, &meta->table[index].value);
		zram_free_page(zram, index);
		bit_spin_unlock(ZRAM_ACCESS, &meta->table[index].value);
		atomic64_inc(&zram->stats.notify_free);
		index++;
		n -= PAGE_SIZE;
	}
}
