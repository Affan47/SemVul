git_treebuilder_get(git_treebuilder *bld, const char *filename)
{
	int idx;
	git_tree_entry *entry;

	assert(bld && filename);

	sort_entries(bld);
	idx = git_vector_bsearch2(&bld->entries, entry_search_cmp, filename);
	if (idx == GIT_ENOTFOUND)
		return NULL;

	entry = git_vector_get(&bld->entries, idx);
	if (entry->removed)
		return NULL;

	return entry;
}
