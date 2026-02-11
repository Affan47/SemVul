tree_unlink_node(struct tree_node *node)
{
	struct tree_node *ni = node->parent;
	if (ni->children == node) {
		ni->children = node->sibling;
	} else {
		ni = ni->children;
		while (ni->sibling != node)
			ni = ni->sibling;
		ni->sibling = node->sibling;
	}
	node->sibling = NULL;
	node->parent = NULL;
}
