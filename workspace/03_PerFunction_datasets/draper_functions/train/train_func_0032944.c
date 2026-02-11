disconnect_model (EReflow *reflow)
{
	if (reflow->model == NULL)
		return;

	g_signal_handler_disconnect (
		reflow->model,
		reflow->model_changed_id);
	g_signal_handler_disconnect (
		reflow->model,
		reflow->comparison_changed_id);
	g_signal_handler_disconnect (
		reflow->model,
		reflow->model_items_inserted_id);
	g_signal_handler_disconnect (
		reflow->model,
		reflow->model_item_removed_id);
	g_signal_handler_disconnect (
		reflow->model,
		reflow->model_item_changed_id);
	g_object_unref (reflow->model);

	reflow->model_changed_id        = 0;
	reflow->comparison_changed_id   = 0;
	reflow->model_items_inserted_id = 0;
	reflow->model_item_removed_id   = 0;
	reflow->model_item_changed_id   = 0;
	reflow->model                   = NULL;
}
