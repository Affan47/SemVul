rotate_left(struct redblack_tree *t, struct rb_node *x)
{
	struct rb_node *y = x->right;
	x->right = y->left;

	if (y->left != nil)
		y->left->parent = x;

	y->parent = x->parent;

	if (x->parent == nil)
		t->root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;

	y->left = x;
	x->parent = y;
}
