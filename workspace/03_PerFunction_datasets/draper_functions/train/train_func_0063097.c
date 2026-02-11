item_changed (EReflowModel *model,
              gint i,
              EReflow *reflow)
{
	if (i < 0 || i >= reflow->count)
		return;

	reflow->heights[i] = e_reflow_model_height (reflow->model, i, GNOME_CANVAS_GROUP (reflow));
	if (reflow->items[i] != NULL)
		e_reflow_model_reincarnate (model, i, reflow->items[i]);
	e_sorter_array_clean (reflow->sorter);
	reflow->reflow_from_column = -1;
	reflow->need_reflow_columns = TRUE;
	e_canvas_item_request_reflow (GNOME_CANVAS_ITEM (reflow));
}
