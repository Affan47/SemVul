merge_trees_from_branches(
	git_index **index, git_repository *repo,
	const char *ours_name, const char *theirs_name,
	git_merge_tree_opts *opts)
{
	git_commit *our_commit, *their_commit, *ancestor_commit = NULL;
	git_tree *our_tree, *their_tree, *ancestor_tree = NULL;
	git_oid our_oid, their_oid, ancestor_oid;
	git_buf branch_buf = GIT_BUF_INIT;
	int error;

	git_buf_printf(&branch_buf, "%s%s", GIT_REFS_HEADS_DIR, ours_name);
	cl_git_pass(git_reference_name_to_id(&our_oid, repo, branch_buf.ptr));
	cl_git_pass(git_commit_lookup(&our_commit, repo, &our_oid));

	git_buf_clear(&branch_buf);
	git_buf_printf(&branch_buf, "%s%s", GIT_REFS_HEADS_DIR, theirs_name);
	cl_git_pass(git_reference_name_to_id(&their_oid, repo, branch_buf.ptr));
	cl_git_pass(git_commit_lookup(&their_commit, repo, &their_oid));

	error = git_merge_base(&ancestor_oid, repo, git_commit_id(our_commit), git_commit_id(their_commit));

	if (error != GIT_ENOTFOUND) {
		cl_git_pass(error);

		cl_git_pass(git_commit_lookup(&ancestor_commit, repo, &ancestor_oid));
		cl_git_pass(git_commit_tree(&ancestor_tree, ancestor_commit));
	}

	cl_git_pass(git_commit_tree(&our_tree, our_commit));
	cl_git_pass(git_commit_tree(&their_tree, their_commit));

	cl_git_pass(git_merge_trees(index, repo, ancestor_tree, our_tree, their_tree, opts));

	git_buf_free(&branch_buf);
	git_tree_free(our_tree);
	git_tree_free(their_tree);
	git_tree_free(ancestor_tree);
	git_commit_free(our_commit);
	git_commit_free(their_commit);
	git_commit_free(ancestor_commit);

	return 0;
}
