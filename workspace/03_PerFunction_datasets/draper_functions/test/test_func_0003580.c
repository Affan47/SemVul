hb_tree_probe(hb_tree *tree, void *key, void **dat)
{
	int rv = 0;
	hb_node *node, *parent = NULL, *q = NULL;

	ASSERT(tree != NULL);

	node = tree->root;
	while (node) {
		rv = tree->key_cmp(key, node->key);
		if (rv < 0)
			parent = node, node = node->llink;
		else if (rv > 0)
			parent = node, node = node->rlink;
		else {
			*dat = node->dat;
			return 0;
		}
		if (parent->bal)
			q = parent;
	}

	if ((node = node_new(key, *dat)) == NULL)
		return -1;
	if ((node->parent = parent) == NULL) {
		tree->root = node;
		ASSERT(tree->count == 0);
		tree->count = 1;
		return 1;
	}
	if (rv < 0)
		parent->llink = node;
	else
		parent->rlink = node;

	while (parent != q) {
		parent->bal = (parent->rlink == node) * 2 - 1;
		node = parent;
		parent = parent->parent;
	}
	if (q) {
		if (q->llink == node) {
			if (--q->bal == -2) {
				if (q->llink->bal > 0)
					rot_left(tree, q->llink);
				rot_right(tree, q);
			}
		} else {
			if (++q->bal == +2) {
				if (q->rlink->bal < 0)
					rot_right(tree, q->rlink);
				rot_left(tree, q);
			}
		}
	}
	tree->count++;
	return 1;
}
