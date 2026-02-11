node_recurse (Node *node)
{
	if (node_right (node))
		return node_right (node);
	if (node_down (node))
		return node_down (node);

	while (node_left (node)) {
		if (node_down (node_left (node)))
			return node_down (node_left (node));
		node = node_left (node);
	}
	return 0;
}
