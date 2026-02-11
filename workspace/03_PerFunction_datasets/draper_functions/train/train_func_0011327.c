test_checkout_tree__can_checkout_with_last_workdir_item_missing(void)
{
	git_index *index = NULL;
	git_checkout_opts opts = GIT_CHECKOUT_OPTS_INIT;
	git_oid tree_id, commit_id;
	git_tree *tree = NULL;
	git_commit *commit = NULL;

	git_repository_index(&index, g_repo);

	opts.checkout_strategy = GIT_CHECKOUT_FORCE;

	cl_git_pass(git_reference_name_to_id(&commit_id, g_repo, "refs/heads/master"));
	cl_git_pass(git_commit_lookup(&commit, g_repo, &commit_id));

	cl_git_pass(git_checkout_tree(g_repo, (git_object *)commit, &opts));
	cl_git_pass(git_repository_set_head(g_repo, "refs/heads/master"));

	cl_git_pass(p_mkdir("./testrepo/this-is-dir", 0777));
	cl_git_mkfile("./testrepo/this-is-dir/contained_file", "content\n");

	cl_git_pass(git_index_add_bypath(index, "this-is-dir/contained_file"));
	git_index_write_tree(&tree_id, index);
	cl_git_pass(git_tree_lookup(&tree, g_repo, &tree_id));

	cl_git_pass(p_unlink("./testrepo/this-is-dir/contained_file"));

	opts.checkout_strategy = GIT_CHECKOUT_SAFE;

	opts.checkout_strategy = 1;
	git_checkout_tree(g_repo, (git_object *)tree, &opts);

	git_tree_free(tree);
	git_commit_free(commit);
	git_index_free(index);
}
