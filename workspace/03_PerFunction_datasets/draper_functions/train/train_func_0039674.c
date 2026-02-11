test_filter_crlf__to_odb(void)
{
	git_filter_list *fl;
	git_filter *crlf;
	git_buf in = { 0 }, out = { 0 };

	cl_git_pass(git_filter_list_new(
		&fl, g_repo, GIT_FILTER_TO_ODB, 0));

	crlf = git_filter_lookup(GIT_FILTER_CRLF);
	cl_assert(crlf != NULL);

	cl_git_pass(git_filter_list_push(fl, crlf, NULL));

	in.ptr = "Some text\r\nRight here\r\n";
	in.size = strlen(in.ptr);

	cl_git_pass(git_filter_list_apply_to_data(&out, fl, &in));

	cl_assert_equal_s("Some text\nRight here\n", out.ptr);

	git_filter_list_free(fl);
	git_buf_free(&out);
}
