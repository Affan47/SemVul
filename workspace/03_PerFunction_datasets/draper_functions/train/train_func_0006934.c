calc_nnode_num_from_parent(const struct ubifs_info *c,
				      struct ubifs_nnode *parent, int iip)
{
	int num, shft;

	if (!parent)
		return 1;
	shft = (c->lpt_hght - parent->level) * UBIFS_LPT_FANOUT_SHIFT;
	num = parent->num ^ (1 << shft);
	num |= (UBIFS_LPT_FANOUT + iip) << shft;
	return num;
}
