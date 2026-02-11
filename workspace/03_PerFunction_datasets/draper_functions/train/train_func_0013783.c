branch_begin(btree_iterator iter)
{
	struct btree_node *node = iter->node->branch[iter->k];
	unsigned int depth = node->depth;
	while (depth--)
		node = node->branch[0];
	iter->node = node;
	iter->k = 0;
}
