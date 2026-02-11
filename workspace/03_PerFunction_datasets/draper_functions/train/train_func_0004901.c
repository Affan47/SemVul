said_branch_node(tree_t pos, int left, int right)
{
	said_tree[pos].type = PARSE_TREE_NODE_BRANCH;

	if (left != VALUE_IGNORE)
		said_tree[pos].content.branches[0] = left;

	if (right != VALUE_IGNORE)
		said_tree[pos].content.branches[1] = right;

	return pos;
}
