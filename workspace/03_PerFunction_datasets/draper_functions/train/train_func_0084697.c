etree_find_depth_internal(const etree_t *tree, node_t *root,
	unsigned curdepth, unsigned maxdepth, match_fn_t match, void *data)
{
	node_t *n, *next;
	void *item;

	etree_check(tree);

	item = ptr_add_offset(root, -tree->offset);

	if ((*match)(item, data))
		return item;

	if (maxdepth == curdepth)
		return NULL;

	for (n = root->child; n != NULL; n = next) {
		next = n->sibling;
		item = etree_find_depth_internal(tree, n,
			curdepth + 1, maxdepth, match, data);
		if (item != NULL)
			return item;
	}

	return NULL;
}
