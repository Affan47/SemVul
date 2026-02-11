git_merge__append_conflicts_to_merge_msg(
	git_repository *repo,
	git_index *index)
{
	git_filebuf file = GIT_FILEBUF_INIT;
	git_buf file_path = GIT_BUF_INIT;
	const char *last = NULL;
	size_t i;
	int error;

	if (!git_index_has_conflicts(index))
		return 0;

	if ((error = git_buf_joinpath(&file_path, repo->path_repository, GIT_MERGE_MSG_FILE)) < 0 ||
		(error = git_filebuf_open(&file, file_path.ptr, GIT_FILEBUF_APPEND, GIT_MERGE_FILE_MODE)) < 0)
		goto cleanup;

	git_filebuf_printf(&file, "\nConflicts:\n");

	for (i = 0; i < git_index_entrycount(index); i++) {
		const git_index_entry *e = git_index_get_byindex(index, i);

		if (git_index_entry_stage(e) == 0)
			continue;

		if (last == NULL || strcmp(e->path, last) != 0)
			git_filebuf_printf(&file, "\t%s\n", e->path);

		last = e->path;
	}

	error = git_filebuf_commit(&file);

cleanup:
	if (error < 0)
		git_filebuf_cleanup(&file);

	git_buf_free(&file_path);

	return error;
}
