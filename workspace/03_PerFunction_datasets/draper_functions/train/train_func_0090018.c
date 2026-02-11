test_object_commit_commitstagedfile__generate_predictable_object_ids(void)
{
	git_index *index;
	const git_index_entry *entry;
	git_oid expected_blob_oid, tree_oid, expected_tree_oid, commit_oid, expected_commit_oid;
	git_signature *signature;
	git_tree *tree;
	git_buf buffer;


	cl_git_pass(git_oid_fromstr(&expected_commit_oid, "1fe3126578fc4eca68c193e4a3a0a14a0704624d"));
	cl_git_pass(git_oid_fromstr(&expected_tree_oid, "2b297e643c551e76cfa1f93810c50811382f9117"));
	cl_git_pass(git_oid_fromstr(&expected_blob_oid, "9daeafb9864cf43055ae93beb0afd6c7d144bfa4"));


	cl_git_mkfile("treebuilder/test.txt", "test\n");
	cl_git_pass(git_repository_index(&index, repo));
	cl_git_pass(git_index_add_bypath(index, "test.txt"));

	entry = git_index_get_byindex(index, 0);

	cl_assert(git_oid_cmp(&expected_blob_oid, &entry->id) == 0);


	{
		struct stat st;
		cl_must_pass(p_lstat("treebuilder/test.txt", &st));
		cl_assert(entry->file_size == st.st_size);
#ifndef _WIN32


		cl_assert(entry->uid == st.st_uid);
		cl_assert(entry->gid == st.st_gid);
#endif
	}


	cl_git_pass(git_index_write_tree(&tree_oid, index));

	cl_assert(git_oid_cmp(&expected_tree_oid, &tree_oid) == 0);


	cl_git_pass(git_signature_new(&signature, "nulltoken", "emeric.fermas@gmail.com", 1323847743, 60));
	cl_git_pass(git_tree_lookup(&tree, repo, &tree_oid));

	memset(&buffer, 0, sizeof(git_buf));
	cl_git_pass(git_message_prettify(&buffer, "Initial commit", 0, '#'));

	cl_git_pass(git_commit_create_v(
		&commit_oid,
		repo,
		"HEAD",
		signature,
		signature,
		NULL,
		buffer.ptr,
		tree,
		0));

	cl_assert(git_oid_cmp(&expected_commit_oid, &commit_oid) == 0);

	git_buf_free(&buffer);
	git_signature_free(signature);
	git_tree_free(tree);
	git_index_free(index);
}
