etree_append_child(etree_t *tree, void *parent, void *child)
{
	node_t *cn, *pn;

	etree_check(tree);
	g_assert(parent != NULL);
	g_assert(child != NULL);
	g_assert(etree_is_orphan(tree, child));

	cn = ptr_add_offset(child, tree->offset);
	pn = ptr_add_offset(parent, tree->offset);

	if (etree_is_extended(tree)) {
		nodex_t *px = ptr_add_offset(parent, tree->offset);

		if (px->last_child != NULL) {
			node_t *lcn = px->last_child;

			g_assert(0 == ptr_cmp(lcn->parent, px));
			g_assert(NULL == lcn->sibling);

			lcn->sibling = cn;
		} else {
			g_assert(NULL == px->child);

			px->child = cn;
		}

		px->last_child = cn;
	} else {
		if (NULL == pn->child) {
			pn->child = cn;
		} else {
			node_t *lcn = etree_node_last_sibling(pn->child);
			lcn->sibling = cn;
		}
	}

	cn->parent = pn;
	tree->count = 0;
}
