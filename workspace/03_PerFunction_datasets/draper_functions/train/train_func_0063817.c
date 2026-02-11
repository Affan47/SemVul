aug_get_base_node(parse_tree_node_t *tree)
{
	int startpos = 0;
	AUG_READ_BRANCH(startpos, 1, startpos);
	return startpos;
}
