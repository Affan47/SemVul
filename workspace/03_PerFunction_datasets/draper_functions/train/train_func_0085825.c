cl_git_path_url(const char *path)
{
	static char url[4096];

	const char *in_buf;
	git_buf path_buf = GIT_BUF_INIT;
	git_buf url_buf = GIT_BUF_INIT;

	cl_git_pass(git_path_prettify_dir(&path_buf, path, NULL));
	cl_git_pass(git_buf_puts(&url_buf, "file://"));

#ifdef GIT_WIN32


	cl_git_pass(git_buf_putc(&url_buf, '/'));
#endif

	in_buf = git_buf_cstr(&path_buf);


	while (*in_buf) {
		if (*in_buf == ' ')
			cl_git_pass(git_buf_puts(&url_buf, "%20"));
		else
			cl_git_pass(git_buf_putc(&url_buf, *in_buf));

		in_buf++;
	}

	strncpy(url, git_buf_cstr(&url_buf), 4096);
	git_buf_free(&url_buf);
	git_buf_free(&path_buf);
	return url;
}
