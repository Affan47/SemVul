test_repo_hashfile__filtered(void)
{
	git_oid a, b;
	git_config *config;

	cl_git_pass(git_repository_config(&config, _repo));
	cl_git_pass(git_config_set_bool(config, "core.autocrlf", true));
	git_config_free(config);

	cl_git_append2file("status/.gitattributes", "*.txt text\n*.bin binary\n\n");


	cl_git_mkfile("status/testfile.txt", "content\r\n");
	cl_git_mkfile("status/testfile.bin", "other\r\nstuff\r\n");


	cl_git_pass(git_odb_hashfile(&a, "status/testfile.txt", GIT_OBJ_BLOB));
	cl_git_pass(git_repository_hashfile(&b, _repo, "testfile.txt", GIT_OBJ_BLOB, NULL));
	cl_assert(git_oid_cmp(&a, &b));


	cl_git_pass(git_odb_hashfile(&a, "status/testfile.bin", GIT_OBJ_BLOB));
	cl_git_pass(git_repository_hashfile(&b, _repo, "testfile.bin", GIT_OBJ_BLOB, NULL));
	cl_assert(git_oid_equal(&a, &b));


	cl_git_pass(git_odb_hashfile(&a, "status/testfile.txt", GIT_OBJ_BLOB));
	cl_git_pass(git_repository_hashfile(&b, _repo, "testfile.txt", GIT_OBJ_BLOB, "foo.bin"));
	cl_assert(git_oid_equal(&a, &b));


	cl_git_pass(git_odb_hashfile(&a, "status/testfile.bin", GIT_OBJ_BLOB));
	cl_git_pass(git_repository_hashfile(&b, _repo, "testfile.bin", GIT_OBJ_BLOB, "foo.txt"));
	cl_assert(git_oid_cmp(&a, &b));


	cl_git_pass(git_odb_hashfile(&a, "status/testfile.txt", GIT_OBJ_BLOB));
	cl_git_pass(git_repository_hashfile(&b, _repo, "testfile.txt", GIT_OBJ_BLOB, ""));
	cl_assert(git_oid_equal(&a, &b));

	cl_git_pass(git_odb_hashfile(&a, "status/testfile.bin", GIT_OBJ_BLOB));
	cl_git_pass(git_repository_hashfile(&b, _repo, "testfile.bin", GIT_OBJ_BLOB, ""));
	cl_assert(git_oid_equal(&a, &b));


	cl_git_fail(git_odb_hashfile(&a, "status/testfile.txt", 0));
	cl_git_fail(git_repository_hashfile(&b, _repo, "testfile.txt", GIT_OBJ_ANY, NULL));
}
