disconnect_adjustment (EReflow *reflow)
{
	if (reflow->adjustment == NULL)
		return;

	g_signal_handler_disconnect (
		reflow->adjustment,
		reflow->adjustment_changed_id);
	g_signal_handler_disconnect (
		reflow->adjustment,
		reflow->adjustment_value_changed_id);

	g_object_unref (reflow->adjustment);

	reflow->adjustment_changed_id = 0;
	reflow->adjustment_value_changed_id = 0;
	reflow->adjustment = NULL;
}
