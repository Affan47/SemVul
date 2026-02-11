hfs_bnode_read_key(struct hfs_bnode *node, void *key, int off)
{
	struct hfs_btree *tree;
	int key_len;

	tree = node->tree;
	if (node->type == HFS_NODE_LEAF ||
	    tree->attributes & HFS_TREE_VARIDXKEYS)
		key_len = hfs_bnode_read_u8(node, off) + 1;
	else
		key_len = tree->max_key_len + 1;

	hfs_bnode_read(node, key, off, key_len);
}
