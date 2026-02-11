findNodeL(BinTreeNode *node, const Object *obj) const
{
	if (!node) return NULL;
	BinTreeNode *lastLower = NULL;
	while (true) {
		int c = compareObjects(obj, node->key);
		if (c <= 0) {
			if (!node->left) return lastLower;
			node = node->left;
		} else {
			if (!node->right) return node;
			lastLower = node;
			node = node->right;
		}
	}
}
