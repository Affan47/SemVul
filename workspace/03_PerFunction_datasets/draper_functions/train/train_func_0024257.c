git_treebuilder_remove(git_treebuilder *bld, const char *filename)
{
	git_tree_entry *entry = treebuilder_get(bld, filename);

	if (entry == NULL)
		return tree_error("Failed to remove entry. File isn't in the tree", filename);

	git_strmap_delete(bld->map, filename);
	git_tree_entry_free(entry);

	return 0;
}
