tree_frompath(
	git_tree **parent_out,
	git_tree *root,
	git_buf *treeentry_path,
	size_t offset)
{
	char *slash_pos = NULL;
	const git_tree_entry* entry;
	int error = 0;
	git_tree *subtree;

	if (!*(treeentry_path->ptr + offset)) {
		giterr_set(GITERR_INVALID,
			"Invalid relative path to a tree entry '%s'.", treeentry_path->ptr);
		return -1;
	}

	slash_pos = (char *)strchr(treeentry_path->ptr + offset, '/');

	if (slash_pos == NULL)
		return git_tree_lookup(
			parent_out,
			root->object.repo,
			git_object_id((const git_object *)root)
		);

	if (slash_pos == treeentry_path->ptr + offset) {
		giterr_set(GITERR_INVALID,
			"Invalid relative path to a tree entry '%s'.", treeentry_path->ptr);
		return -1;
	}

	*slash_pos = '\0';

	entry = git_tree_entry_byname(root, treeentry_path->ptr + offset);

	if (slash_pos != NULL)
		*slash_pos = '/';

	if (entry == NULL) {
		giterr_set(GITERR_TREE,
			"No tree entry can be found from "
			"the given tree and relative path '%s'.", treeentry_path->ptr);
		return GIT_ENOTFOUND;
	}


	if (git_tree_lookup(&subtree, root->object.repo, &entry->oid) < 0)
		return error;

	error = tree_frompath(
		parent_out,
		subtree,
		treeentry_path,
		(slash_pos - treeentry_path->ptr) + 1
	);

	git_tree_free(subtree);
	return error;
}
