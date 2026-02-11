node_next(hb_node *node)
{
	hb_node *temp;

	ASSERT(node != NULL);

	if (node->rlink) {
		for (node = node->rlink; node->llink; node = node->llink)
			;
		return node;
	}
	temp = node->parent;
	while (temp && temp->rlink == node) {
		node = temp;
		temp = temp->parent;
	}
	return temp;
}
