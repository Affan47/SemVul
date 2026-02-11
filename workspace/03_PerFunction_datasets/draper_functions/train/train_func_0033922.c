statusbar_calc_item_positions(STATUSBAR_REC *bar)
{
        WINDOW_REC *old_active_win;
	GSList *tmp, *right_items;
	int xpos, rxpos;

	old_active_win = active_win;
        if (bar->parent_window != NULL)
		active_win = bar->parent_window->active;

	statusbar_resize_items(bar, term_width);


	xpos = 0;
	for (tmp = bar->items; tmp != NULL; tmp = tmp->next) {
		SBAR_ITEM_REC *rec = tmp->data;

		if (!rec->config->right_alignment &&
		    (rec->size > 0 || rec->current_size > 0)) {
			if (SBAR_ITEM_REDRAW_NEEDED(bar, rec, xpos)) {

				rec->dirty = TRUE;
				if (bar->dirty_xpos == -1 ||
				    xpos < bar->dirty_xpos) {
                                        irssi_set_dirty();
					bar->dirty = TRUE;
					bar->dirty_xpos = xpos;
				}

				rec->xpos = xpos;
			}
			xpos += rec->size;
		}
	}


        right_items = NULL;
	for (tmp = bar->items; tmp != NULL; tmp = tmp->next) {
		SBAR_ITEM_REC *rec = tmp->data;

		if (rec->config->right_alignment) {
                        if (rec->size > 0)
				right_items = g_slist_prepend(right_items, rec);
			else if (rec->current_size > 0 &&
				 (bar->dirty_xpos == -1 ||
				  rec->xpos < bar->dirty_xpos)) {


				irssi_set_dirty();
				bar->dirty = TRUE;
                                bar->dirty_xpos = rec->xpos;
			}
		}
	}

	rxpos = term_width;
	for (tmp = right_items; tmp != NULL; tmp = tmp->next) {
		SBAR_ITEM_REC *rec = tmp->data;

		rxpos -= rec->size;
		if (SBAR_ITEM_REDRAW_NEEDED(bar, rec, rxpos)) {
			rec->dirty = TRUE;
			if (bar->dirty_xpos == -1 ||
			    rxpos < bar->dirty_xpos) {
				irssi_set_dirty();
				bar->dirty = TRUE;
				bar->dirty_xpos = rxpos;
			}
			rec->xpos = rxpos;
		}
	}
        g_slist_free(right_items);

	active_win = old_active_win;
}
