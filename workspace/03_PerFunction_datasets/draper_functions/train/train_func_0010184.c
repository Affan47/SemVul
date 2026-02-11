find_node(HTT *htt, unsigned u,
	hash_item_header **father, int *leftson, int reduced)
{
	hash_item_header *node = TREE(u);
	hash_item_header *nodef = NULL;
	int ls;

	u &= ~1U;
	while (node != NULL) {
		unsigned v = *(unsigned *)(node->ident);
		unsigned w = v & ~1U;

		if (u == w) break;
		nodef = node;
		if (u < w) {
			node = node->left;
			ls = 1;
		} else {
			node = node->right;
			ls = 0;
		}
	}
	if (father != NULL) {
		*father = nodef;
		*leftson = ls;
	}
	return node;
}
