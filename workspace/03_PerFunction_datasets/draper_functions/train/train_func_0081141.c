tree_free (Node *node)
{
	Node *root = node_root (node);

	while (node_down (root))
		node_remove (node_down (root));

	root = node_remove (root);
	node_free (root);

	return;
}
