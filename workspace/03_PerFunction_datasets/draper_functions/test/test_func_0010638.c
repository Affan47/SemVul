tree_draw(struct view *view, struct line *line, unsigned int lineno)
{
	struct tree_entry *entry = line->data;

	if (line->type == LINE_TREE_HEAD) {
		if (draw_text(view, line->type, "Directory path /"))
			return TRUE;
	} else {
		if (draw_mode(view, entry->mode))
			return TRUE;

		if (draw_author(view, entry->author))
			return TRUE;

		if (draw_date(view, &entry->time))
			return TRUE;
	}

	draw_text(view, line->type, entry->name);
	return TRUE;
}
