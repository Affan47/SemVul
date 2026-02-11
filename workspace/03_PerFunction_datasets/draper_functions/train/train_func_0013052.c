bb_uncle (MonoSimpleBasicBlock *bb)
{
	MonoSimpleBasicBlock *gp = bb_grandparent (bb);
	if (gp == NULL)
		return NULL;
	if (bb->parent == gp->left)
		return gp->right;
	return gp->left;
}
