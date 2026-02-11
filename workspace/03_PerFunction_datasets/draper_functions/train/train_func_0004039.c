rotate_right (MonoSimpleBasicBlock *parent, MonoSimpleBasicBlock **root)
{
	MonoSimpleBasicBlock *bb = parent->left;
	if (bb->right) {
		parent->left = bb->right;
		parent->left->parent = parent;
	} else
		parent->left = NULL;
	bb->right = parent;
	change_node (parent, bb, root);
	parent->parent = bb;
}
