items_inserted (EReflowModel *model,
                gint position,
                gint count,
                EReflow *reflow)
{
	gint i, oldcount;

	if (position < 0 || position > reflow->count)
		return;

	oldcount = reflow->count;

	reflow->count += count;

	if (reflow->count > reflow->allocated_count) {
		while (reflow->count > reflow->allocated_count)
			reflow->allocated_count += 256;
		reflow->heights = g_renew (int, reflow->heights, reflow->allocated_count);
		reflow->items = g_renew (GnomeCanvasItem *, reflow->items, reflow->allocated_count);
	}
	memmove (reflow->heights + position + count, reflow->heights + position, (reflow->count - position - count) * sizeof (gint));
	memmove (reflow->items + position + count, reflow->items + position, (reflow->count - position - count) * sizeof (GnomeCanvasItem *));
	for (i = position; i < position + count; i++) {
		reflow->items[i] = NULL;
		reflow->heights[i] = e_reflow_model_height (reflow->model, i, GNOME_CANVAS_GROUP (reflow));
	}

	e_selection_model_simple_set_row_count (E_SELECTION_MODEL_SIMPLE (reflow->selection), reflow->count);
	if (position == oldcount)
		e_sorter_array_append (reflow->sorter, count);
	else
		e_sorter_array_set_count (reflow->sorter, reflow->count);

	for (i = position; i < position + count; i++) {
		gint sorted = e_sorter_model_to_sorted (E_SORTER (reflow->sorter), i);
		gint c;

		for (c = reflow->column_count - 1; c >= 0; c--) {
			gint start_of_column = reflow->columns[c];

			if (start_of_column <= sorted) {
				if (reflow->reflow_from_column == -1
				    || reflow->reflow_from_column > c) {
					reflow->reflow_from_column = c;
				}
				break;
			}
		}
	}

	reflow->need_reflow_columns = TRUE;
	set_empty (reflow);
	e_canvas_item_request_reflow (GNOME_CANVAS_ITEM (reflow));
}
