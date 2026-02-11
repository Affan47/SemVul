stage_diff_write(struct io *io, struct line *line, struct line *end)
{
	while (line < end) {
		if (!io_write(io, line->data, strlen(line->data)) ||
		    !io_write(io, "\n", 1))
			return FALSE;
		line++;
		if (line->type == LINE_DIFF_CHUNK ||
		    line->type == LINE_DIFF_HEADER)
			break;
	}

	return TRUE;
}
