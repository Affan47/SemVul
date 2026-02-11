lookup(const AVL *avl, AvlNode *node, const void *key)
{
	int cmp;

	if (node == NULL)
		return NULL;

	cmp = avl->compare(key, node->key);

	if (cmp < 0)
		return lookup(avl, node->lr[0], key);
	if (cmp > 0)
		return lookup(avl, node->lr[1], key);
	return node;
}
