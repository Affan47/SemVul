nilfs_btree_do_lookup(const struct nilfs_bmap *btree,
				 struct nilfs_btree_path *path,
				 __u64 key, __u64 *ptrp, int minlevel,
				 int readahead)
{
	struct nilfs_btree_node *node;
	struct nilfs_btree_readahead_info p, *ra;
	__u64 ptr;
	int level, index, found, ncmax, ret;

	node = nilfs_btree_get_root(btree);
	level = nilfs_btree_node_get_level(node);
	if (level < minlevel || nilfs_btree_node_get_nchildren(node) <= 0)
		return -ENOENT;

	found = nilfs_btree_node_lookup(node, key, &index);
	ptr = nilfs_btree_node_get_ptr(node, index,
				       NILFS_BTREE_ROOT_NCHILDREN_MAX);
	path[level].bp_bh = NULL;
	path[level].bp_index = index;

	ncmax = nilfs_btree_nchildren_per_block(btree);

	while (--level >= minlevel) {
		ra = NULL;
		if (level == NILFS_BTREE_LEVEL_NODE_MIN && readahead) {
			p.node = nilfs_btree_get_node(btree, path, level + 1,
						      &p.ncmax);
			p.index = index;
			p.max_ra_blocks = 7;
			ra = &p;
		}
		ret = __nilfs_btree_get_block(btree, ptr, &path[level].bp_bh,
					      ra);
		if (ret < 0)
			return ret;

		node = nilfs_btree_get_nonroot_node(path, level);
		if (nilfs_btree_bad_node(node, level))
			return -EINVAL;
		if (!found)
			found = nilfs_btree_node_lookup(node, key, &index);
		else
			index = 0;
		if (index < ncmax) {
			ptr = nilfs_btree_node_get_ptr(node, index, ncmax);
		} else {
			WARN_ON(found || level != NILFS_BTREE_LEVEL_NODE_MIN);

			ptr = NILFS_BMAP_INVALID_PTR;
		}
		path[level].bp_index = index;
	}
	if (!found)
		return -ENOENT;

	if (ptrp != NULL)
		*ptrp = ptr;

	return 0;
}
