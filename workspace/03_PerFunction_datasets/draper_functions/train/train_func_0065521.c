stage_apply_chunk(struct view *view, struct line *chunk, bool revert)
{
	const char *apply_argv[SIZEOF_ARG] = {
		"git", "apply", "--whitespace=nowarn", NULL
	};
	struct line *diff_hdr;
	struct io io;
	int argc = 3;

	diff_hdr = stage_diff_find(view, chunk, LINE_DIFF_HEADER);
	if (!diff_hdr)
		return FALSE;

	if (!revert)
		apply_argv[argc++] = "--cached";
	if (revert || stage_line_type == LINE_STAT_STAGED)
		apply_argv[argc++] = "-R";
	apply_argv[argc++] = "-";
	apply_argv[argc++] = NULL;
	if (!io_run(&io, IO_WR, opt_cdup, apply_argv))
		return FALSE;

	if (!stage_diff_write(&io, diff_hdr, chunk) ||
	    !stage_diff_write(&io, chunk, view->line + view->lines))
		chunk = NULL;

	io_done(&io);
	io_run_bg(update_index_argv);

	return chunk ? TRUE : FALSE;
}
