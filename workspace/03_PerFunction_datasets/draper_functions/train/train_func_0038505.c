loadR(ObjectStream &s, BinTreeNode *&n, int l, int r)
{
	if (l > r) {
		n = NULL;
		return 0;
	}
	n = allocNode();
	uint m = (l+r)/2;

	int L = loadR(s, n->left, l, m-1);

	n->key = s.getObject("element", hom_objid);

	int R = loadR(s, n->right, m+1, r);

	if (L < R) {
		n->unbalance = +1;
	} else if (L > R) {
		n->unbalance = -1;
	} else {
		n->unbalance = 0;
	}
	return MAX(L, R)+1;
}
