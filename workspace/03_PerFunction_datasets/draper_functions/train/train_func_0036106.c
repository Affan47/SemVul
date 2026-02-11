show_man_page(const char *git_cmd)
{
	const char *page;

	if (!prefixcmp(git_cmd, "git"))
		page = git_cmd;
	else {
		int page_len = strlen(git_cmd) + 4;
		char *p = xmalloc(page_len + 1);
		strcpy(p, "git-");
		strcpy(p + 4, git_cmd);
		p[page_len] = 0;
		page = p;
	}

	execlp("man", "man", page, NULL);
}
