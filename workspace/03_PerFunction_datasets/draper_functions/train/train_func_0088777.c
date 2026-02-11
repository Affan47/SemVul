trbt_delete32(trbt_tree_t *tree, uint32_t key)
{
	trbt_node_t *node;

	node=tree->root;

	while(node){
		if(key==node->key32){
			talloc_free(node);
			return;
		}
		if(key<node->key32){
			node=node->left;
			continue;
		}
		if(key>node->key32){
			node=node->right;
			continue;
		}
	}
}
