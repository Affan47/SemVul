get_button_list_from_main(List *button_list, int start, int end,
				      int color_inx)
{
	ListIterator itr = NULL;
	ListIterator button_itr = NULL;
	grid_button_t *grid_button = NULL;
	grid_button_t *send_grid_button = NULL;

	if (!*button_list)
		*button_list = list_create(destroy_grid_button);

	color_inx %= sview_colors_cnt;
	itr = list_iterator_create(grid_button_list);
	while ((grid_button = list_next(itr))) {
		if ((grid_button->inx < start)
		    ||  (grid_button->inx > end))
			continue;
		button_itr = list_iterator_create(*button_list);
		while ((send_grid_button = list_next(button_itr))) {
			if (send_grid_button->inx == grid_button->inx)
				break;
		}
		list_iterator_destroy(button_itr);
		if (send_grid_button)
			continue;

		send_grid_button = create_grid_button_from_another(
			grid_button, grid_button->node_name, color_inx);
		if (send_grid_button) {
			send_grid_button->button_list = *button_list;
			_add_button_signals(send_grid_button);
			list_append(*button_list, send_grid_button);
		}
	}
	list_iterator_destroy(itr);
	return;
}
