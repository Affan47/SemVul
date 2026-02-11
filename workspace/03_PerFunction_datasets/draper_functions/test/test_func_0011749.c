load_repo_info(void)
{
	const char *head_argv[] = {
		"git", "symbolic-ref", "HEAD", NULL
	};
	const char *rev_parse_argv[] = {
		"git", "rev-parse", "--git-dir", "--is-inside-work-tree",
			"--show-cdup", NULL
	};

	if (run_io_buf(head_argv, opt_head, sizeof(opt_head))) {
		chomp_string(opt_head);
		if (!prefixcmp(opt_head, "refs/heads/")) {
			char *offset = opt_head + STRING_SIZE("refs/heads/");

			memmove(opt_head, offset, strlen(offset) + 1);
		}
	}

	return git_properties(rev_parse_argv, "=", read_repo_info);
}
