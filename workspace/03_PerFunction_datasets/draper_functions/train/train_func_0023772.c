find_row_start(struct window *window, position_t position,
				 position_t start)
{
	size_t bytes;
	if (position && position >= window->view->bytes)
		position--;
	while ((bytes = find_row_bytes(window->view, start, 0, window->columns))) {
		if (start + bytes > position)
			break;
		start += bytes;
	}
	return start;
}
