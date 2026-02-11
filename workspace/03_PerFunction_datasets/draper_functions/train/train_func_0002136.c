git_ignore__check_pathspec_for_exact_ignores(
	git_repository *repo,
	git_vector *vspec,
	bool no_fnmatch)
{
	int error = 0;
	size_t i;
	git_attr_fnmatch *match;
	int ignored;
	git_buf path = GIT_BUF_INIT;
	const char *wd, *filename;
	git_index *idx;

	if ((error = git_repository__ensure_not_bare(
			repo, "validate pathspec")) < 0 ||
		(error = git_repository_index(&idx, repo)) < 0)
		return error;

	wd = git_repository_workdir(repo);

	git_vector_foreach(vspec, i, match) {

		if ((match->flags & GIT_ATTR_FNMATCH_HASWILD) != 0 &&
			!no_fnmatch)
			continue;

		filename = match->pattern;


		if (git_index_get_bypath(idx, filename, 0) != NULL)
			continue;

		if ((error = git_buf_joinpath(&path, wd, filename)) < 0)
			break;


		if (!git_path_isfile(path.ptr))
			continue;


		if ((error = git_ignore_path_is_ignored(&ignored, repo, filename)) < 0)
			break;

		if (ignored) {
			giterr_set(GITERR_INVALID, "pathspec contains ignored file '%s'",
				filename);
			error = GIT_EINVALIDSPEC;
			break;
		}
	}

	git_index_free(idx);
	git_buf_free(&path);

	return error;
}
