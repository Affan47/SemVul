highlight_grid_range(int start, int end, List button_list)
{
	ListIterator itr = NULL;
	grid_button_t *grid_button = NULL;

	if (!button_list)
		return;

	itr = list_iterator_create(button_list);
	while ((grid_button = list_next(itr))) {
		if (start != -1)
			if ((grid_button->inx < start)
			    || (grid_button->inx > end)) {

				if ((GTK_WIDGET_STATE(grid_button->button)
				     != GTK_STATE_ACTIVE))
					gtk_widget_set_state(
						grid_button->button,
						GTK_STATE_ACTIVE);
				continue;
			}


		if ((GTK_WIDGET_STATE(grid_button->button)
		     != GTK_STATE_NORMAL))
			gtk_widget_set_state(grid_button->button,
					     GTK_STATE_NORMAL);
	}
	list_iterator_destroy(itr);

	return;
}
