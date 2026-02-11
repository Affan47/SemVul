said_leaf_node(tree_t pos, int value)
{
	said_tree[pos].type = PARSE_TREE_NODE_LEAF;

	if (value != VALUE_IGNORE)
		said_tree[pos].content.value = value;

	return pos;
}
