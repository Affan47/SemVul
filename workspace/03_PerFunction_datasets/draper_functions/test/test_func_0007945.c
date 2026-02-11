git_pathspec__match_at(
	size_t *matched_at,
	const git_vector *vspec,
	struct pathspec_match_context *ctxt,
	const char *path0,
	const char *path1)
{
	int result = GIT_ENOTFOUND;
	size_t i = 0;
	const git_attr_fnmatch *match;

	git_vector_foreach(vspec, i, match) {
		if (path0 && (result = pathspec_match_one(match, ctxt, path0)) >= 0)
			break;
		if (path1 && (result = pathspec_match_one(match, ctxt, path1)) >= 0)
			break;
	}

	*matched_at = i;
	return result;
}
