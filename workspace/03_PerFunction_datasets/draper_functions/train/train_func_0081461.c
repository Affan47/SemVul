clone_node(const hash_item_header *node, void *(*clone)(const void *))
{
	hash_item_header *cleft, *cright, *cnode;
	unsigned v;

	if (node == NULL) return NULL;
	cleft = clone_node(node->left, clone);
	cright = clone_node(node->right, clone);
	v = *(unsigned *)(node->ident);
	if ((v & 1U) != 0) {
		hash_item_header *pnode, **pcpnode;

		cnode = getmem(sizeof *node);
		cnode->ident = clone_ident(node->ident);
		pcpnode = (hash_item_header **)(cnode->ident + PTR_SHIFT);
		for (pnode = *(hash_item_header **)(node->ident + PTR_SHIFT);
			pnode != NULL; pnode = pnode->left) {
			*pcpnode = clone(pnode);
			(*pcpnode)->ident = clone_ident(pnode->ident);
			pcpnode = &((*pcpnode)->left);
		}
		*pcpnode = NULL;
	} else {
		cnode = clone(node);
		cnode->ident = clone_ident(node->ident);
	}
	cnode->left = cleft;
	cnode->right = cright;
	return cnode;
}
