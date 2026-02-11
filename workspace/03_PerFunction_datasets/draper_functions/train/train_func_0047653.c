action_move_to_next_pane_callback (GtkAction *action, gpointer callback_data)
{
	NemoWindowSlot *slot;
	char *dest_location;
	NemoView *view;

	view = NEMO_VIEW (callback_data);

	slot = nemo_window_get_extra_slot (nemo_view_get_nemo_window (view));
	g_return_if_fail (slot != NULL);

	dest_location = nemo_window_slot_get_current_uri (slot);
	g_return_if_fail (dest_location != NULL);

	move_copy_selection_to_location (view, GDK_ACTION_MOVE, dest_location);
}
