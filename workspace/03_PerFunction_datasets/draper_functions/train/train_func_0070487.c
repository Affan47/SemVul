eti_remove_selection_model (ETableItem *eti)
{
	if (!eti->selection)
		return;

	g_signal_handler_disconnect (
		eti->selection,
		eti->selection_change_id);
	g_signal_handler_disconnect (
		eti->selection,
		eti->selection_row_change_id);
	g_signal_handler_disconnect (
		eti->selection,
		eti->cursor_change_id);
	g_signal_handler_disconnect (
		eti->selection,
		eti->cursor_activated_id);
	g_object_unref (eti->selection);

	eti->selection_change_id = 0;
	eti->selection_row_change_id = 0;
	eti->cursor_activated_id = 0;
	eti->selection = NULL;
}
