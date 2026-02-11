display_area(const char *text, const byte *attrs,
		size_t *line_starts, size_t *line_lengths,
		size_t n_lines,
		region area, size_t line_from)
{
	size_t i, j;

	n_lines = MIN(n_lines, (size_t) area.page_rows);

	for (i = 0; i < n_lines; i++) {
		Term_erase(area.col, area.row + i, area.width);
		for (j = 0; j < line_lengths[line_from + i]; j++) {
			Term_putch(area.col + j, area.row + i,
					attrs[line_starts[line_from + i] + j],
					text[line_starts[line_from + i] + j]);
		}
	}
}
