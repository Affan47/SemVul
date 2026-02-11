test_object_tree_attributes__normalize_600(void)
{
	git_oid id;
	git_tree *tree;
	git_repository *repo;
	const git_tree_entry *entry;

	repo = cl_git_sandbox_init("deprecated-mode.git");

	git_oid_fromstr(&id, "0810fb7818088ff5ac41ee49199b51473b1bd6c7");
	cl_git_pass(git_tree_lookup(&tree, repo, &id));

	entry = git_tree_entry_byname(tree, "ListaTeste.xml");
	cl_assert_equal_i(git_tree_entry_filemode(entry), GIT_FILEMODE_BLOB);
	cl_assert_equal_i(git_tree_entry_filemode_raw(entry), 0100600);

	git_tree_free(tree);
	cl_git_sandbox_cleanup();
}
