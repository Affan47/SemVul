findPrev(ObjHandle h) const
{
	if (!validHandle(h)) return findLast();
	BinTreeNode *n = handleToNative(h);
	if (n->left) return nativeToHandle(getRightmost(n->left));
	BinTreeNode *x = root, *result = NULL;
	while (x) {
		int c = compareObjects(x->key, n->key);
		if (c < 0) {
			result = x;
			x = x->right;
		} else {
			x = x->left;
		}
	}
	return nativeToHandle(result);
}
