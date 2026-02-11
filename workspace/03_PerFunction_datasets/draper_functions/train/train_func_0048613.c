git_attr_file__out_of_date(git_repository *repo, git_attr_file *file)
{
	if (!file)
		return 1;

	switch (file->source) {
	case GIT_ATTR_FILE__IN_MEMORY:
		return 0;

	case GIT_ATTR_FILE__FROM_FILE:
		return git_futils_filestamp_check(
			&file->cache_data.stamp, file->entry->fullpath);

	case GIT_ATTR_FILE__FROM_INDEX: {
		int error;
		git_oid id;

		if ((error = attr_file_oid_from_index(
				&id, repo, file->entry->path)) < 0)
			return error;

		return (git_oid__cmp(&file->cache_data.oid, &id) != 0);
	}

	default:
		giterr_set(GITERR_INVALID, "Invalid file type %d", file->source);
		return -1;
	}
}
