stage_diff_write(FILE *pipe, struct line *line, struct line *end)
{
	while (line < end) {
		if (!stage_diff_line(pipe, line++))
			return FALSE;
		if (line->type == LINE_DIFF_CHUNK ||
		    line->type == LINE_DIFF_HEADER)
			break;
	}

	return TRUE;
}
