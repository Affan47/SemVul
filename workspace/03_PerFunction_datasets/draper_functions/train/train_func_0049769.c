commit_staged_files(
	git_oid *commit_oid,
	git_index *index,
	git_signature *signature)
{
	git_tree *tree;
	git_oid tree_oid;
	git_repository *repo;

	repo = git_index_owner(index);

	cl_git_pass(git_index_write_tree(&tree_oid, index));

	cl_git_pass(git_tree_lookup(&tree, repo, &tree_oid));

	cl_git_pass(git_commit_create_v(
		commit_oid,
		repo,
		"HEAD",
		signature,
		signature,
		NULL,
		"Initial commit",
		tree,
		0));

	git_tree_free(tree);
}
