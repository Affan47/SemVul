status_update_prepare(struct io *io, enum line_type type)
{
	const char *staged_argv[] = {
		"git", "update-index", "-z", "--index-info", NULL
	};
	const char *others_argv[] = {
		"git", "update-index", "-z", "--add", "--remove", "--stdin", NULL
	};

	switch (type) {
	case LINE_STAT_STAGED:
		return run_io(io, staged_argv, opt_cdup, IO_WR);

	case LINE_STAT_UNSTAGED:
		return run_io(io, others_argv, opt_cdup, IO_WR);

	case LINE_STAT_UNTRACKED:
		return run_io(io, others_argv, NULL, IO_WR);

	default:
		die("line type %d not handled in switch", type);
		return FALSE;
	}
}
