add_line_data(struct view *view, void *data, enum line_type type)
{
	struct line *line;

	if (!realloc_lines(&view->line, view->lines, 1))
		return NULL;

	line = &view->line[view->lines++];
	memset(line, 0, sizeof(*line));
	line->type = type;
	line->data = data;
	line->dirty = 1;

	return line;
}
