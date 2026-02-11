aatree_walk(aatree_t *t, int direction)
{
	if ((direction == AATREE_WALK_LEFT) && (t->left != &bottom))
		return t->left;

	if ((direction == AATREE_WALK_RIGHT) && (t->right != &bottom))
		return t->right;

	return NULL;
}
