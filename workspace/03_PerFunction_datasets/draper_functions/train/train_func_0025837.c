comp_items(const struct item_head *stored_ih, const struct treepath *path)
{
	struct buffer_head *bh = PATH_PLAST_BUFFER(path);
	struct item_head *ih;


	if (!B_IS_IN_TREE(bh))
		return 1;


	if (PATH_LAST_POSITION(path) >= B_NR_ITEMS(bh))
		return 1;


	ih = tp_item_head(path);
	return memcmp(stored_ih, ih, IH_SIZE);
}
