statusbar_item_redraw(SBAR_ITEM_REC *item)
{
        WINDOW_REC *old_active_win;

	g_return_if_fail(item != NULL);

	old_active_win = active_win;
        if (item->bar->parent_window != NULL)
		active_win = item->bar->parent_window->active;

	item->func(item, TRUE);

	item->dirty = TRUE;
	item->bar->dirty = TRUE;
	irssi_set_dirty();

	if (item->max_size != item->size) {


		statusbar_redraw(item->bar, FALSE);
	}

	active_win = old_active_win;
}
