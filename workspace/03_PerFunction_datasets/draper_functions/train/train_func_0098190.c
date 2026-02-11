window_page_up(struct view *view)
{
	struct window *window = view->window;
	position_t start = screen_start(view);
	position_t end;
	int row;
	size_t bytes;

	if (start) {
		int overlap = page_overlap(window);
		for (row = 0;
		     (end = start) && row + overlap < window->rows;
		     row += count_rows(window, start, end))
			start = find_line_start(view, start-1);
		while (row-- + overlap > window->rows)
			start += find_row_bytes(view, start,
						0, window->columns);
		new_start(view, start);
		for (row = 0; row < window->rows-1; row++, start += bytes)
			if (!(bytes = find_row_bytes(view, start, 0,
						     window->columns)))
				break;
		display_insert_lines(display, window->row, window->column,
				     window->rows - overlap,
				     window->rows, window->columns);
	}
	locus_set(view, CURSOR, start);
}
