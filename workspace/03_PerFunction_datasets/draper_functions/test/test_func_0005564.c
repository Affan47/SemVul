path_exists(struct tree *tree, const char *path)
{
	const char *pathspec[] = { path, NULL };

	if (read_tree_recursive(tree, "", 0, 0, pathspec, reject_entry, NULL))
		return 1;
	return 0;
}
