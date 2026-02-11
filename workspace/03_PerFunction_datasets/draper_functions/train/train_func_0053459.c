ensure_there_are_changes_to_stash(
	git_repository *repo,
	bool include_untracked_files,
	bool include_ignored_files)
{
	int error;
	git_status_options opts = GIT_STATUS_OPTIONS_INIT;

	opts.show  = GIT_STATUS_SHOW_INDEX_AND_WORKDIR;
	opts.flags = GIT_STATUS_OPT_EXCLUDE_SUBMODULES;

	if (include_untracked_files)
		opts.flags |= GIT_STATUS_OPT_INCLUDE_UNTRACKED |
			GIT_STATUS_OPT_RECURSE_UNTRACKED_DIRS;

	if (include_ignored_files)
		opts.flags |= GIT_STATUS_OPT_INCLUDE_IGNORED |
			GIT_STATUS_OPT_RECURSE_IGNORED_DIRS;

	error = git_status_foreach_ext(repo, &opts, is_dirty_cb, NULL);

	if (error == GIT_PASSTHROUGH)
		return 0;

	if (!error)
		return create_error(GIT_ENOTFOUND, "There is nothing to stash.");

	return error;
}
