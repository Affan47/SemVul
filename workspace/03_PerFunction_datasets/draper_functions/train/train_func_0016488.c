status_update_onbranch(void)
{
	static const char *paths[][2] = {
		{ "rebase-apply/rebasing",	"Rebasing" },
		{ "rebase-apply/applying",	"Applying mailbox" },
		{ "rebase-apply/",		"Rebasing mailbox" },
		{ "rebase-merge/interactive",	"Interactive rebase" },
		{ "rebase-merge/",		"Rebase merge" },
		{ "MERGE_HEAD",			"Merging" },
		{ "BISECT_LOG",			"Bisecting" },
		{ "HEAD",			"On branch" },
	};
	char buf[SIZEOF_STR];
	struct stat stat;
	int i;

	if (is_initial_commit()) {
		string_copy(status_onbranch, "Initial commit");
		return;
	}

	for (i = 0; i < ARRAY_SIZE(paths); i++) {
		char *head = opt_head;

		if (!string_format(buf, "%s/%s", opt_git_dir, paths[i][0]) ||
		    lstat(buf, &stat) < 0)
			continue;

		if (!*opt_head) {
			struct io io = {};

			if (string_format(buf, "%s/rebase-merge/head-name", opt_git_dir) &&
			    io_open(&io, buf) &&
			    io_read_buf(&io, buf, sizeof(buf))) {
				head = chomp_string(buf);
				if (!prefixcmp(head, "refs/heads/"))
					head += STRING_SIZE("refs/heads/");
			}
		}

		if (!string_format(status_onbranch, "%s %s", paths[i][1], head))
			string_copy(status_onbranch, opt_head);
		return;
	}

	string_copy(status_onbranch, "Not currently on any branch");
}
