hfs_bnode_findhash(struct hfs_btree *tree, u32 cnid)
{
	struct hfs_bnode *node;

	if (cnid >= tree->node_count) {
		pr_err("request for non-existent node %d in B*Tree\n", cnid);
		return NULL;
	}

	for (node = tree->node_hash[hfs_bnode_hash(cnid)];
	     node; node = node->next_hash) {
		if (node->this == cnid) {
			return node;
		}
	}
	return NULL;
}
