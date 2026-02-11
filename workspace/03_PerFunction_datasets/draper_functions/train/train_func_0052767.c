stage_revert(struct view *view, struct line *line)
{
	struct line *chunk = NULL;

	if (!opt_no_head && stage_line_type == LINE_STAT_UNSTAGED)
		chunk = stage_diff_find(view, line, LINE_DIFF_CHUNK);

	if (chunk) {
		if (!prompt_yesno("Are you sure you want to revert changes?"))
			return FALSE;

		if (!stage_apply_chunk(view, chunk, TRUE)) {
			report("Failed to revert chunk");
			return FALSE;
		}
		return TRUE;

	} else {
		return status_revert(stage_status.status ? &stage_status : NULL,
				     stage_line_type, FALSE);
	}
}
