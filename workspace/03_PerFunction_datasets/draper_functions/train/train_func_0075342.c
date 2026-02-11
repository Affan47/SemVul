find_origin(
		git_blame *blame,
		git_commit *parent,
		git_blame__origin *origin)
{
	git_blame__origin *porigin = NULL;
	git_diff *difflist = NULL;
	git_diff_options diffopts = GIT_DIFF_OPTIONS_INIT;
	git_tree *otree=NULL, *ptree=NULL;


	if (0 != git_commit_tree(&otree, origin->commit) ||
	    0 != git_commit_tree(&ptree, parent))
		goto cleanup;


	diffopts.context_lines = 0;
	diffopts.flags = GIT_DIFF_SKIP_BINARY_CHECK;


	diffopts.pathspec.count = blame->paths.length;
	diffopts.pathspec.strings = (char**)blame->paths.contents;
	if (0 != git_diff_tree_to_tree(&difflist, blame->repository, ptree, otree, &diffopts))
			goto cleanup;

	if (!git_diff_num_deltas(difflist)) {

		git_blame__get_origin(&porigin, blame, parent, origin->path);
	} else {
		git_diff_find_options findopts = GIT_DIFF_FIND_OPTIONS_INIT;
		int i;


		git_diff_free(difflist);
		diffopts.pathspec.count = 0;
		if (0 != git_diff_tree_to_tree(&difflist, blame->repository, ptree, otree, &diffopts))
			goto cleanup;


		findopts.flags = GIT_DIFF_FIND_RENAMES;
		if (0 != git_diff_find_similar(difflist, &findopts))
			goto cleanup;


		for (i=0; i<(int)git_diff_num_deltas(difflist); i++) {
			const git_diff_delta *delta = git_diff_get_delta(difflist, i);

			if (!git_vector_bsearch(NULL, &blame->paths, delta->new_file.path))
			{
				git_vector_insert_sorted(&blame->paths, (void*)git__strdup(delta->old_file.path),
						paths_on_dup);
				make_origin(&porigin, parent, delta->old_file.path);
			}
		}
	}

cleanup:
	git_diff_free(difflist);
	git_tree_free(otree);
	git_tree_free(ptree);
	return porigin;
}
