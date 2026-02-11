pager_draw(struct view *view, struct line *line, unsigned int lineno, bool selected)
{
	static char spaces[] = "                    ";
	char *text = line->data;
	int col = 0;

	if (opt_line_number) {
		col += draw_lineno(view, lineno, view->width, selected);
		if (col >= view->width)
			return TRUE;
	}

	if (!selected)
		wattrset(view->win, get_line_attr(line->type));

	if (opt_tab_size < TABSIZE) {
		int col_offset = col;

		col = 0;
		while (text && col_offset + col < view->width) {
			int cols_max = view->width - col_offset - col;
			char *pos = text;
			int cols;

			if (*text == '\t') {
				text++;
				assert(sizeof(spaces) > TABSIZE);
				pos = spaces;
				cols = opt_tab_size - (col % opt_tab_size);

			} else {
				text = strchr(text, '\t');
				cols = line ? text - pos : strlen(pos);
			}

			waddnstr(view->win, pos, MIN(cols, cols_max));
			col += cols;
		}

	} else {
		draw_text(view, text, view->width - col, TRUE, selected);
	}

	return TRUE;
}
