rb_next(struct rb_node *node)
{


	if (node->rb_right) {
		node = node->rb_right;
		while (node->rb_left)
			node=node->rb_left;
		return node;
	}


	while (node->rb_parent && node == node->rb_parent->rb_right)
		node = node->rb_parent;

	return node->rb_parent;
}
