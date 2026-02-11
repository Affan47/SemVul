stage_update_chunk(struct view *view, struct line *chunk)
{
	char cmd[SIZEOF_STR];
	size_t cmdsize = 0;
	struct line *diff_hdr;
	FILE *pipe;

	diff_hdr = stage_diff_find(view, chunk, LINE_DIFF_HEADER);
	if (!diff_hdr)
		return FALSE;

	if (opt_cdup[0] &&
	    !string_format_from(cmd, &cmdsize, "cd %s;", opt_cdup))
		return FALSE;

	if (!string_format_from(cmd, &cmdsize,
				"git apply --whitespace=nowarn --cached %s - && "
				"git update-index -q --unmerged --refresh 2>/dev/null",
				stage_line_type == LINE_STAT_STAGED ? "-R" : ""))
		return FALSE;

	pipe = popen(cmd, "w");
	if (!pipe)
		return FALSE;

	if (!stage_diff_write(pipe, diff_hdr, chunk) ||
	    !stage_diff_write(pipe, chunk, view->line + view->lines))
		chunk = NULL;

	pclose(pipe);

	return chunk ? TRUE : FALSE;
}
