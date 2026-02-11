test_object_tree_attributes__normalize_attributes_when_inserting_in_a_new_tree(void)
{
	git_repository *repo;
	git_treebuilder *builder;
	git_oid bid, tid;
	git_tree *tree;
	const git_tree_entry *entry;

	repo = cl_git_sandbox_init("deprecated-mode.git");

	cl_git_pass(git_oid_fromstr(&bid, blob_oid));

	cl_git_pass(git_treebuilder_create(&builder, NULL));

	cl_git_pass(git_treebuilder_insert(
		&entry,
		builder,
		"normalized.txt",
		&bid,
		GIT_FILEMODE_BLOB_GROUP_WRITABLE));

	cl_assert_equal_i(
		GIT_FILEMODE_BLOB,
		git_tree_entry_filemode(entry));

	cl_git_pass(git_treebuilder_write(&tid, repo, builder));
	git_treebuilder_free(builder);

	cl_git_pass(git_tree_lookup(&tree, repo, &tid));

	entry = git_tree_entry_byname(tree, "normalized.txt");
	cl_assert_equal_i(
		GIT_FILEMODE_BLOB,
		git_tree_entry_filemode(entry));

	git_tree_free(tree);
	cl_git_sandbox_cleanup();
}
