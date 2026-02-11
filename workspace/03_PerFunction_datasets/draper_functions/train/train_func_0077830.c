test_checkout_index__options_disable_filters(void)
{
	cl_git_mkfile("./testrepo/.gitattributes", "*.txt text eol=crlf\n");

	g_opts.disable_filters = false;
	cl_git_pass(git_checkout_index(g_repo, NULL, &g_opts));

	test_file_contents("./testrepo/new.txt", "my new file\r\n");

	p_unlink("./testrepo/new.txt");

	g_opts.disable_filters = true;
	cl_git_pass(git_checkout_index(g_repo, NULL, &g_opts));

	test_file_contents("./testrepo/new.txt", "my new file\n");
}
