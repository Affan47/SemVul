cgroup_walk_tree_begin(const char *controller, const char *base_path,
		int depth, void **handle, struct cgroup_file_info *info,
							int *base_level)
{
	int ret = 0;
	char *cg_path[2];
	char full_path[FILENAME_MAX];
	FTSENT *ent;
	struct cgroup_tree_handle *entry;

	if (!cgroup_initialized)
		return ECGROUPNOTINITIALIZED;

	if (!handle)
		return ECGINVAL;

	cgroup_dbg("path is %s\n", base_path);

	if (!cg_build_path(base_path, full_path, controller))
		return ECGOTHER;

	entry = calloc(sizeof(struct cgroup_tree_handle), 1);

	if (!entry) {
		last_errno = errno;
		*handle = NULL;
		return ECGOTHER;
	}

	entry->flags |= CGROUP_WALK_TYPE_PRE_DIR;

	*base_level = 0;
	cg_path[0] = full_path;
	cg_path[1] = NULL;

	entry->fts = fts_open(cg_path, FTS_LOGICAL | FTS_NOCHDIR |
				FTS_NOSTAT, NULL);
	if (entry->fts == NULL) {
		free(entry);
		last_errno = errno;
		*handle = NULL;
		return ECGOTHER;
	}
	ent = fts_read(entry->fts);
	if (!ent) {
		cgroup_dbg("fts_read failed\n");
		fts_close(entry->fts);
		free(entry);
		*handle = NULL;
		return ECGINVAL;
	}
	if (!*base_level && depth)
		*base_level = ent->fts_level + depth;

	ret = cg_walk_node(entry->fts, ent, *base_level, info, entry->flags);
	if (ret != 0) {
		fts_close(entry->fts);
		free(entry);
		*handle = NULL;
	} else {
		*handle = entry;
	}
	return ret;
}
