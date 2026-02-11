trbt_sibling(trbt_node_t *node)
{
	trbt_node_t *parent;

	parent=trbt_parent(node);
	if(!parent){
		return NULL;
	}

	if (node == parent->left) {
		return parent->right;
	} else {
		return parent->left;
	}
}
