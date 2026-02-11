lock_extent_buffer_for_io(struct extent_buffer *eb,
			  struct btrfs_fs_info *fs_info,
			  struct extent_page_data *epd)
{
	unsigned long i, num_pages;
	int flush = 0;
	int ret = 0;

	if (!btrfs_try_tree_write_lock(eb)) {
		flush = 1;
		flush_write_bio(epd);
		btrfs_tree_lock(eb);
	}

	if (test_bit(EXTENT_BUFFER_WRITEBACK, &eb->bflags)) {
		btrfs_tree_unlock(eb);
		if (!epd->sync_io)
			return 0;
		if (!flush) {
			flush_write_bio(epd);
			flush = 1;
		}
		while (1) {
			wait_on_extent_buffer_writeback(eb);
			btrfs_tree_lock(eb);
			if (!test_bit(EXTENT_BUFFER_WRITEBACK, &eb->bflags))
				break;
			btrfs_tree_unlock(eb);
		}
	}


	spin_lock(&eb->refs_lock);
	if (test_and_clear_bit(EXTENT_BUFFER_DIRTY, &eb->bflags)) {
		set_bit(EXTENT_BUFFER_WRITEBACK, &eb->bflags);
		spin_unlock(&eb->refs_lock);
		btrfs_set_header_flag(eb, BTRFS_HEADER_FLAG_WRITTEN);
		__percpu_counter_add(&fs_info->dirty_metadata_bytes,
				     -eb->len,
				     fs_info->dirty_metadata_batch);
		ret = 1;
	} else {
		spin_unlock(&eb->refs_lock);
	}

	btrfs_tree_unlock(eb);

	if (!ret)
		return ret;

	num_pages = num_extent_pages(eb->start, eb->len);
	for (i = 0; i < num_pages; i++) {
		struct page *p = eb->pages[i];

		if (!trylock_page(p)) {
			if (!flush) {
				flush_write_bio(epd);
				flush = 1;
			}
			lock_page(p);
		}
	}

	return ret;
}
