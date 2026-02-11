rbt_print_subtree(

	const ib_rbt_t*		tree,
	const ib_rbt_node_t*	node,
	ib_rbt_print_node	print)
{

	if (node != tree->nil) {
		print(node);
		rbt_print_subtree(tree, node->left, print);
		rbt_print_subtree(tree, node->right, print);
	}
}
