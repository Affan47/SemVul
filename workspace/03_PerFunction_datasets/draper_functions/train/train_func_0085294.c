assert_conflict(
	const char *entry_path,
	const char *new_content,
	const char *parent_sha,
	const char *commit_sha)
{
	git_index *index;
	git_object *hack_tree;
	git_reference *branch, *head;
	git_buf file_path = GIT_BUF_INIT;

	cl_git_pass(git_repository_index(&index, g_repo));


	cl_git_pass(git_revparse_single(&g_object, g_repo, parent_sha));
	cl_git_pass(git_branch_create(&branch, g_repo,
		"potential_conflict", (git_commit *)g_object, 0, NULL, NULL));


	cl_git_pass(git_reference_symbolic_create(
		&head, g_repo, "HEAD", git_reference_name(branch), 1, NULL, NULL));
	git_reference_free(head);
	git_reference_free(branch);


	g_opts.checkout_strategy = GIT_CHECKOUT_FORCE;
	cl_git_pass(git_checkout_tree(g_repo, g_object, &g_opts));


	cl_git_pass(git_object_peel(&hack_tree, g_object, GIT_OBJ_TREE));
	cl_git_pass(git_index_read_tree(index, (git_tree *)hack_tree));
	git_object_free(hack_tree);
	git_object_free(g_object);
	g_object = NULL;


	cl_git_pass(git_buf_joinpath(&file_path, "./testrepo", entry_path));
	cl_git_mkfile(git_buf_cstr(&file_path), new_content);
	git_buf_free(&file_path);


	cl_git_pass(git_revparse_single(&g_object, g_repo, commit_sha));

	g_opts.checkout_strategy = GIT_CHECKOUT_SAFE;
	cl_assert_equal_i(
		GIT_EMERGECONFLICT, git_checkout_tree(g_repo, g_object, &g_opts));


	cl_git_pass(git_index_add_bypath(index, entry_path));
	cl_git_pass(git_index_write(index));
	git_index_free(index);

	cl_assert_equal_i(
		GIT_EMERGECONFLICT, git_checkout_tree(g_repo, g_object, &g_opts));
}
