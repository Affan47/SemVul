btree_order(struct bkey *k)
{
	return ilog2(KEY_SIZE(k) / PAGE_SECTORS ?: 1);
}
