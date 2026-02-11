cgroup_walk_tree_end(void **handle)
{
	struct cgroup_tree_handle *entry;

	if (!cgroup_initialized)
		return ECGROUPNOTINITIALIZED;

	if (!handle)
		return ECGINVAL;

	entry = (struct cgroup_tree_handle *) *handle;

	fts_close(entry->fts);
	free(entry);
	*handle = NULL;
	return 0;
}
