git_tree_cache_get(const git_tree_cache *tree, const char *path)
{
	const char *ptr = path, *end;

	if (tree == NULL) {
		return NULL;
	}

	while (1) {
		end = strchr(ptr, '/');

		tree = find_child(tree, ptr, end);
		if (tree == NULL)
			return NULL;

		if (end == NULL || *end + 1 == '\0')
			return tree;

		ptr = end + 1;
	}
}
