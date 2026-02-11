logfs_truncate_i0(struct inode *inode, struct page *page,
		struct write_control *wc, u64 size)
{
	struct logfs_shadow *shadow;
	u64 bix;
	level_t level;
	int err = 0;

	logfs_unpack_index(page->index, &bix, &level);
	BUG_ON(level != 0);
	shadow = alloc_shadow(inode, bix, level, wc->ofs);

	err = truncate_data_block(inode, page, wc->ofs, shadow, size);
	if (err) {
		free_shadow(inode, shadow);
		return err;
	}

	logfs_segment_delete(inode, shadow);
	set_iused(inode, shadow);
	fill_shadow_tree(inode, page, shadow);
	wc->ofs = shadow->new_ofs;
	return 0;
}
