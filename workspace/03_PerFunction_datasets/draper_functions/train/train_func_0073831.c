__mm_add(struct ibv_mem_node *new)
{
	struct ibv_mem_node *node, *parent = NULL;

	node = mm_root;
	while (node) {
		parent = node;
		if (node->start < new->start)
			node = node->right;
		else
			node = node->left;
	}

	if (parent->start < new->start)
		parent->right = new;
	else
		parent->left = new;

	new->parent = parent;
	new->left   = NULL;
	new->right  = NULL;

	new->color = IBV_RED;
	__mm_add_rebalance(new);
}
