stage_open(struct view *view, enum open_flags flags)
{
	static const char *no_head_diff_argv[] = {
		"git", "diff", ENCODING_ARG, "--no-color", "--patch-with-stat",
			opt_diff_context_arg, opt_ignore_space_arg,
			"--", "/dev/null", stage_status.new.name, NULL
	};
	static const char *index_show_argv[] = {
		"git", "diff-index", ENCODING_ARG, "--root", "--patch-with-stat", "-C", "-M",
			"--cached", opt_diff_context_arg, opt_ignore_space_arg,
			"HEAD", "--",
			stage_status.old.name, stage_status.new.name, NULL
	};
	static const char *files_show_argv[] = {
		"git", "diff-files", ENCODING_ARG, "--root", "--patch-with-stat", "-C", "-M",
			opt_diff_context_arg, opt_ignore_space_arg, "--",
			stage_status.old.name, stage_status.new.name, NULL
	};


	static const char *files_unmerged_argv[] = {
		"git", "diff-files", ENCODING_ARG, "--root", "--patch-with-stat", "-C", "-M",
			opt_diff_context_arg, opt_ignore_space_arg, "--",
			stage_status.old.name, NULL
	};
	static const char *file_argv[] = { opt_cdup, stage_status.new.name, NULL };
	const char **argv = NULL;
	const char *info;

	view->encoding = NULL;

	switch (stage_line_type) {
	case LINE_STAT_STAGED:
		if (is_initial_commit()) {
			argv = no_head_diff_argv;
		} else {
			argv = index_show_argv;
		}
		if (stage_status.status)
			info = "Staged changes to %s";
		else
			info = "Staged changes";
		break;

	case LINE_STAT_UNSTAGED:
		if (stage_status.status != 'U')
			argv = files_show_argv;
		else
			argv = files_unmerged_argv;
		if (stage_status.status)
			info = "Unstaged changes to %s";
		else
			info = "Unstaged changes";
		break;

	case LINE_STAT_UNTRACKED:
		info = "Untracked file %s";
		argv = file_argv;
		view->encoding = get_path_encoding(stage_status.old.name, opt_encoding);
		break;

	case LINE_STAT_HEAD:
	default:
		die("line type %d not handled in switch", stage_line_type);
	}

	string_format(view->ref, info, stage_status.new.name);
	view->vid[0] = 0;
	view->dir = opt_cdup;
	return argv_copy(&view->argv, argv)
	    && begin_update(view, NULL, NULL, flags);
}
