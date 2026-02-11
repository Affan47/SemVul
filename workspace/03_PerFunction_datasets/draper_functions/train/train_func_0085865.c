rename_remote_references(
	git_repository *repo,
	const char *old_name,
	const char *new_name)
{
	int error;
	git_buf buf = GIT_BUF_INIT;
	git_reference *ref;
	git_reference_iterator *iter;

	if ((error = git_buf_printf(&buf, GIT_REFS_REMOTES_DIR "%s/*", old_name)) < 0)
		return error;

	error = git_reference_iterator_glob_new(&iter, repo, git_buf_cstr(&buf));
	git_buf_free(&buf);

	if (error < 0)
		return error;

	while ((error = git_reference_next(&ref, iter)) == 0) {
		if ((error = rename_one_remote_reference(ref, old_name, new_name)) < 0)
			break;
	}

	git_reference_iterator_free(iter);

	return (error == GIT_ITEROVER) ? 0 : error;
}
