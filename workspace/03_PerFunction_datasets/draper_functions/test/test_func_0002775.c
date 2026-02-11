nilfs_btree_node_broken(const struct nilfs_btree_node *node,
				   size_t size, sector_t blocknr)
{
	int level, flags, nchildren;
	int ret = 0;

	level = nilfs_btree_node_get_level(node);
	flags = nilfs_btree_node_get_flags(node);
	nchildren = nilfs_btree_node_get_nchildren(node);

	if (unlikely(level < NILFS_BTREE_LEVEL_NODE_MIN ||
		     level >= NILFS_BTREE_LEVEL_MAX ||
		     (flags & NILFS_BTREE_NODE_ROOT) ||
		     nchildren < 0 ||
		     nchildren > NILFS_BTREE_NODE_NCHILDREN_MAX(size))) {
		printk(KERN_CRIT "NILFS: bad btree node (blocknr=%llu): "
		       "level = %d, flags = 0x%x, nchildren = %d\n",
		       (unsigned long long)blocknr, level, flags, nchildren);
		ret = 1;
	}
	return ret;
}
