test_object_tree_attributes__group_writable_tree_entries_created_with_an_antique_git_version_can_still_be_accessed(void)
{
	git_repository *repo;
	git_oid tid;
	git_tree *tree;
	const git_tree_entry *entry;

	cl_git_pass(git_repository_open(&repo, cl_fixture("deprecated-mode.git")));

	cl_git_pass(git_oid_fromstr(&tid, tree_oid));
	cl_git_pass(git_tree_lookup(&tree, repo, &tid));

	entry = git_tree_entry_byname(tree, "old_mode.txt");
	cl_assert_equal_i(
		GIT_FILEMODE_BLOB,
		git_tree_entry_filemode(entry));

	git_tree_free(tree);
	git_repository_free(repo);
}
