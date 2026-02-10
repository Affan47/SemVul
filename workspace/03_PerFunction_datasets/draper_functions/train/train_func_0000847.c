new_line(size_t **line_starts, size_t **line_lengths,
		size_t *n_lines, size_t *cur_line,
		size_t start, size_t len)
{
	if (*cur_line == *n_lines) {

		(*n_lines) += 24;

		*line_starts = mem_realloc(*line_starts,
				*n_lines * sizeof **line_starts);
		*line_lengths = mem_realloc(*line_lengths,
				*n_lines * sizeof **line_lengths);
	}

	(*line_starts)[*cur_line] = start;
	(*line_lengths)[*cur_line] = len;

	(*cur_line)++;
}
