_display_tree(CMD_ARGS)
{
	if (!_build_whole_deptree(cmd))
		return 0;

	_display_tree_walk_children(dm_tree_find_node(_dtree, 0, 0), 0);

	return 1;
}
