single_dirent_cb(void *state, char *full_path)
{
	struct status_st *st = (struct status_st *)state;
	struct status_entry *e = st->entry.e;

	char *file_path = full_path + st->workdir_path_len;
	struct stat filest;
	git_oid oid;

	if ((git_futils_isdir(full_path) == GIT_SUCCESS) && (!strcmp(".git", file_path)))
		return 0;

	if (git_futils_isdir(full_path) == GIT_SUCCESS)
		return git_futils_direach(full_path, GIT_PATH_MAX, single_dirent_cb, state);

	if (!strcmp(file_path, e->path)) {
		if (p_stat(full_path, &filest) < 0)
			return git__throw(GIT_EOSERR, "Failed to read file %s", full_path);

		if (e->mtime.seconds == (git_time_t)filest.st_mtime) {
			git_oid_cpy(&e->wt_oid, &e->index_oid);
			return 1;
		}

		git_odb_hashfile(&oid, full_path, GIT_OBJ_BLOB);
		git_oid_cpy(&e->wt_oid, &oid);
		return 1;
	}

	return 0;
}
