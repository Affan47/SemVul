ext_tree_mark_written(struct pnfs_block_layout *bl, sector_t start,
		sector_t len)
{
	struct rb_root *root = &bl->bl_ext_rw;
	sector_t end = start + len;
	struct pnfs_block_extent *be;
	int err = 0;

	spin_lock(&bl->bl_ext_lock);


	err = __ext_tree_remove(&bl->bl_ext_ro, start, end);
	if (err)
		goto out;


	for (be = __ext_tree_search(root, start); be; be = ext_tree_next(be)) {
		if (be->be_f_offset >= end)
			break;

		if (be->be_state != PNFS_BLOCK_INVALID_DATA || be->be_tag)
			continue;

		if (be->be_f_offset < start) {
			struct pnfs_block_extent *left = ext_tree_prev(be);

			if (left && ext_can_merge(left, be)) {
				sector_t diff = start - be->be_f_offset;

				left->be_length += diff;

				be->be_f_offset += diff;
				be->be_v_offset += diff;
				be->be_length -= diff;
			} else {
				err = ext_tree_split(root, be, start);
				if (err)
					goto out;
			}
		}

		if (ext_f_end(be) > end) {
			struct pnfs_block_extent *right = ext_tree_next(be);

			if (right && ext_can_merge(be, right)) {
				sector_t diff = end - be->be_f_offset;

				be->be_length -= diff;

				right->be_f_offset -= diff;
				right->be_v_offset -= diff;
				right->be_length += diff;
			} else {
				err = ext_tree_split(root, be, end);
				if (err)
					goto out;
			}
		}

		if (be->be_f_offset >= start && ext_f_end(be) <= end) {
			be->be_tag = EXTENT_WRITTEN;
			be = ext_try_to_merge_left(root, be);
			be = ext_try_to_merge_right(root, be);
		}
	}
out:
	spin_unlock(&bl->bl_ext_lock);
	return err;
}
