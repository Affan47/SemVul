__ext_tree_remove(struct rb_root *root, sector_t start, sector_t end)
{
	struct pnfs_block_extent *be;
	sector_t len1 = 0, len2 = 0;
	sector_t orig_v_offset;
	sector_t orig_len;

	be = __ext_tree_search(root, start);
	if (!be)
		return 0;
	if (be->be_f_offset >= end)
		return 0;

	orig_v_offset = be->be_v_offset;
	orig_len = be->be_length;

	if (start > be->be_f_offset)
		len1 = start - be->be_f_offset;
	if (ext_f_end(be) > end)
		len2 = ext_f_end(be) - end;

	if (len2 > 0) {
		if (len1 > 0) {
			struct pnfs_block_extent *new;

			new = kzalloc(sizeof(*new), GFP_ATOMIC);
			if (!new)
				return -ENOMEM;

			be->be_length = len1;

			new->be_f_offset = end;
			if (be->be_state != PNFS_BLOCK_NONE_DATA) {
				new->be_v_offset =
					orig_v_offset + orig_len - len2;
			}
			new->be_length = len2;
			new->be_state = be->be_state;
			new->be_tag = be->be_tag;
			new->be_device = nfs4_get_deviceid(be->be_device);

			__ext_tree_insert(root, new, true);
		} else {
			be->be_f_offset = end;
			if (be->be_state != PNFS_BLOCK_NONE_DATA) {
				be->be_v_offset =
					orig_v_offset + orig_len - len2;
			}
			be->be_length = len2;
		}
	} else {
		if (len1 > 0) {
			be->be_length = len1;
			be = ext_tree_next(be);
		}

		while (be && ext_f_end(be) <= end) {
			struct pnfs_block_extent *next = ext_tree_next(be);

			rb_erase(&be->be_node, root);
			nfs4_put_deviceid_node(be->be_device);
			kfree(be);
			be = next;
		}

		if (be && be->be_f_offset < end) {
			len1 = ext_f_end(be) - end;
			be->be_f_offset = end;
			if (be->be_state != PNFS_BLOCK_NONE_DATA)
				be->be_v_offset += be->be_length - len1;
			be->be_length = len1;
		}
	}

	return 0;
}
