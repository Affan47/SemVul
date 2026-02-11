pathspec_mark_remaining(
	git_bitvec *used,
	git_vector *patterns,
	struct pathspec_match_context *ctxt,
	size_t start,
	const char *path0,
	const char *path1)
{
	size_t count = 0;

	if (path1 == path0)
		path1 = NULL;

	for (; start < patterns->length; ++start) {
		const git_attr_fnmatch *pat = git_vector_get(patterns, start);

		if (git_bitvec_get(used, start))
			continue;

		if (path0 && pathspec_match_one(pat, ctxt, path0) > 0)
			count += pathspec_mark_pattern(used, start);
		else if (path1 && pathspec_match_one(pat, ctxt, path1) > 0)
			count += pathspec_mark_pattern(used, start);
	}

	return count;
}
