recalculate_thresholds(struct btrfs_free_space_ctl *ctl)
{
	struct btrfs_block_group_cache *block_group = ctl->private;
	u64 max_bytes;
	u64 bitmap_bytes;
	u64 extent_bytes;
	u64 size = block_group->key.offset;
	u32 bytes_per_bg = BITS_PER_BITMAP * ctl->unit;
	u32 max_bitmaps = div_u64(size + bytes_per_bg - 1, bytes_per_bg);

	max_bitmaps = max_t(u32, max_bitmaps, 1);

	ASSERT(ctl->total_bitmaps <= max_bitmaps);


	if (size < 1024 * 1024 * 1024)
		max_bytes = MAX_CACHE_BYTES_PER_GIG;
	else
		max_bytes = MAX_CACHE_BYTES_PER_GIG *
			div_u64(size, 1024 * 1024 * 1024);


	bitmap_bytes = (ctl->total_bitmaps + 1) * PAGE_CACHE_SIZE;

	if (bitmap_bytes >= max_bytes) {
		ctl->extents_thresh = 0;
		return;
	}


	extent_bytes = max_bytes - bitmap_bytes;
	extent_bytes = min_t(u64, extent_bytes, max_bytes >> 1);

	ctl->extents_thresh =
		div_u64(extent_bytes, sizeof(struct btrfs_free_space));
}
