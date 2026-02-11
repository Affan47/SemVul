blame_draw(struct view *view, struct line *line, unsigned int lineno)
{
	struct blame *blame = line->data;
	struct time *time = NULL;
	const char *id = NULL, *author = NULL;
	char text[SIZEOF_STR];

	if (blame->commit && *blame->commit->filename) {
		id = blame->commit->id;
		author = blame->commit->author;
		time = &blame->commit->time;
	}

	if (opt_date && draw_date(view, time))
		return TRUE;

	if (opt_author && draw_author(view, author))
		return TRUE;

	if (draw_field(view, LINE_BLAME_ID, id, ID_COLS, FALSE))
		return TRUE;

	if (draw_lineno(view, lineno))
		return TRUE;

	string_expand(text, sizeof(text), blame->text, opt_tab_size);
	draw_text(view, LINE_DEFAULT, text, TRUE);
	return TRUE;
}
