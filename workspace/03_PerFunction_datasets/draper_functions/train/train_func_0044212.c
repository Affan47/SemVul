test_object_tree_attributes__treebuilder_reject_invalid_filemode(void)
{
	git_treebuilder *builder;
	git_oid bid;
	const git_tree_entry *entry;

	cl_git_pass(git_oid_fromstr(&bid, blob_oid));
	cl_git_pass(git_treebuilder_create(&builder, NULL));

	cl_git_fail(git_treebuilder_insert(
		&entry,
		builder,
		"normalized.txt",
		&bid,
		GIT_FILEMODE_BLOB_GROUP_WRITABLE));

	git_treebuilder_free(builder);
}
