nilfs_btree_propagate_v(struct nilfs_bmap *btree,
				   struct nilfs_btree_path *path,
				   int level, struct buffer_head *bh)
{
	int maxlevel = 0, ret;
	struct nilfs_btree_node *parent;
	struct inode *dat = nilfs_bmap_get_dat(btree);
	__u64 ptr;
	int ncmax;

	get_bh(bh);
	path[level].bp_bh = bh;
	ret = nilfs_btree_prepare_propagate_v(btree, path, level, &maxlevel,
					      dat);
	if (ret < 0)
		goto out;

	if (buffer_nilfs_volatile(path[level].bp_bh)) {
		parent = nilfs_btree_get_node(btree, path, level + 1, &ncmax);
		ptr = nilfs_btree_node_get_ptr(parent,
					       path[level + 1].bp_index,
					       ncmax);
		ret = nilfs_dat_mark_dirty(dat, ptr);
		if (ret < 0)
			goto out;
	}

	nilfs_btree_commit_propagate_v(btree, path, level, maxlevel, bh, dat);

 out:
	brelse(path[level].bp_bh);
	path[level].bp_bh = NULL;
	return ret;
}
