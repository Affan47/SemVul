git_treebuilder_remove(git_treebuilder *bld, const char *filename)
{
	git_tree_entry *remove_ptr = (git_tree_entry *)git_treebuilder_get(bld, filename);

	if (remove_ptr == NULL || remove_ptr->removed)
		return GIT_ENOTFOUND;

	remove_ptr->removed = 1;
	bld->entry_count--;
	return GIT_SUCCESS;
}
