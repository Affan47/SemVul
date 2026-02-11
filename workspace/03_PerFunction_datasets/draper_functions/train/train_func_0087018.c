test_refs_rename__loose(void)
{

	git_reference *looked_up_ref, *another_looked_up_ref;
	git_buf temp_path = GIT_BUF_INIT;
	const char *new_name = "refs/tags/Nemo/knows/refs.kung-fu";


	cl_git_pass(git_buf_joinpath(&temp_path, g_repo->path_repository, new_name));
	cl_assert(!git_path_exists(temp_path.ptr));


	cl_git_pass(git_reference_lookup(&looked_up_ref, g_repo, loose_tag_ref_name));


	cl_assert(git_reference_is_packed(looked_up_ref) == 0);


	cl_git_pass(git_reference_rename(looked_up_ref, new_name, 0));
	cl_assert_equal_s(looked_up_ref->name, new_name);


	cl_git_fail(git_reference_lookup(&another_looked_up_ref, g_repo, loose_tag_ref_name));


	cl_git_pass(git_reference_lookup(&another_looked_up_ref, g_repo, new_name));
	cl_assert_equal_s(another_looked_up_ref->name, new_name);


	cl_assert(git_reference_is_packed(another_looked_up_ref) == 0);
	cl_assert(git_reference_is_packed(looked_up_ref) == 0);


	cl_git_pass(git_buf_joinpath(&temp_path, g_repo->path_repository, new_name));
	cl_assert(git_path_exists(temp_path.ptr));

	git_reference_free(looked_up_ref);
	git_reference_free(another_looked_up_ref);
	git_buf_free(&temp_path);
}
