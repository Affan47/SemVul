etree_prepend_child(etree_t *tree, void *parent, void *child)
{
	node_t *cn, *pn;

	etree_check(tree);
	g_assert(parent != NULL);
	g_assert(child != NULL);
	g_assert(etree_is_orphan(tree, child));

	cn = ptr_add_offset(child, tree->offset);
	pn = ptr_add_offset(parent, tree->offset);

	cn->parent = pn;
	cn->sibling = pn->child;
	pn->child = cn;

	if (etree_is_extended(tree)) {
		nodex_t *px = (nodex_t *) pn;

		if (NULL == px->last_child) {
			g_assert(NULL == cn->sibling);
			px->last_child = cn;
		}
	}

	tree->count = 0;
}
