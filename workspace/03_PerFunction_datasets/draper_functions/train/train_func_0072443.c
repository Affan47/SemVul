test_refs_delete__packed_loose(void)
{

	git_reference *looked_up_ref, *another_looked_up_ref;
	git_buf temp_path = GIT_BUF_INIT;


	cl_git_pass(git_buf_joinpath(&temp_path, g_repo->path_repository, packed_test_head_name));
	cl_assert(git_path_exists(temp_path.ptr));


	cl_git_pass(git_reference_lookup(&looked_up_ref, g_repo, packed_test_head_name));


	cl_assert(git_reference_is_packed(looked_up_ref) == 0);


	cl_git_pass(git_reference_delete(looked_up_ref));


	cl_git_fail(git_reference_lookup(&another_looked_up_ref, g_repo, packed_test_head_name));


	cl_assert(!git_path_exists(temp_path.ptr));

	git_reference_free(another_looked_up_ref);
	git_buf_free(&temp_path);
}
