cgroup_walk_tree_next(int depth, void **handle,
				struct cgroup_file_info *info, int base_level)
{
	int ret = 0;
	struct cgroup_tree_handle *entry;
	FTSENT *ent;

	if (!cgroup_initialized)
		return ECGROUPNOTINITIALIZED;

	if (!handle)
		return ECGINVAL;

	entry = (struct cgroup_tree_handle *) *handle;

	ent = fts_read(entry->fts);
	if (!ent)
		return ECGEOF;
	if (!base_level && depth)
		base_level = ent->fts_level + depth;

	ret = cg_walk_node(entry->fts, ent, base_level, info, entry->flags);

	*handle = entry;
	return ret;
}
