handle_grep_syntax(git_object **out, git_repository *repo, const git_oid *spec_oid, const char *pattern)
{
	regex_t preg;
	git_revwalk *walk = NULL;
	int error;

	if ((error = build_regex(&preg, pattern)) < 0)
		return error;

	if ((error = git_revwalk_new(&walk, repo)) < 0)
		goto cleanup;

	git_revwalk_sorting(walk, GIT_SORT_TIME);

	if (spec_oid == NULL) {

		if ((error = git_revwalk_push_glob(walk, GIT_REFS_HEADS_DIR "*")) < 0)
			goto cleanup;
	} else if ((error = git_revwalk_push(walk, spec_oid)) < 0)
			goto cleanup;

	error = walk_and_search(out, walk, &preg);

cleanup:
	regfree(&preg);
	git_revwalk_free(walk);

	return error;
}
