test_core_buffer__puts_escaped(void)
{
	git_buf a = GIT_BUF_INIT;

	git_buf_clear(&a);
	cl_git_pass(git_buf_text_puts_escaped(&a, "this is a test", "", ""));
	cl_assert_equal_s("this is a test", a.ptr);

	git_buf_clear(&a);
	cl_git_pass(git_buf_text_puts_escaped(&a, "this is a test", "t", "\\"));
	cl_assert_equal_s("\\this is a \\tes\\t", a.ptr);

	git_buf_clear(&a);
	cl_git_pass(git_buf_text_puts_escaped(&a, "this is a test", "i ", "__"));
	cl_assert_equal_s("th__is__ __is__ a__ test", a.ptr);

	git_buf_clear(&a);
	cl_git_pass(git_buf_text_puts_escape_regex(&a, "^match\\s*[A-Z]+.*"));
	cl_assert_equal_s("\\^match\\\\s\\*\\[A-Z\\]\\+\\.\\*", a.ptr);

	git_buf_free(&a);
}
