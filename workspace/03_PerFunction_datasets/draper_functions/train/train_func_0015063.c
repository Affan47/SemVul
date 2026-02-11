said_value(int val, tree_t t)
{
	return said_branch_node(SAID_NEXT_NODE,
				said_leaf_node(SAID_NEXT_NODE, val),
				t
				);

}
