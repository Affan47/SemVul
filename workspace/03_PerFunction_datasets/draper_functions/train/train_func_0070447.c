validate_pnode(const struct ubifs_info *c, struct ubifs_pnode *pnode,
			  struct ubifs_nnode *parent, int iip)
{
	int i;

	if (c->big_lpt) {
		int num = calc_pnode_num_from_parent(c, parent, iip);

		if (pnode->num != num)
			return -EINVAL;
	}
	for (i = 0; i < UBIFS_LPT_FANOUT; i++) {
		int free = pnode->lprops[i].free;
		int dirty = pnode->lprops[i].dirty;

		if (free < 0 || free > c->leb_size || free % c->min_io_size ||
		    (free & 7))
			return -EINVAL;
		if (dirty < 0 || dirty > c->leb_size || (dirty & 7))
			return -EINVAL;
		if (dirty + free > c->leb_size)
			return -EINVAL;
	}
	return 0;
}
