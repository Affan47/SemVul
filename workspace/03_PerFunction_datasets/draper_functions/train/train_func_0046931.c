nautilus_window_go_to_full (NautilusWindow *window,
			    GFile          *location,
			    NautilusWindowGoToCallback callback,
			    gpointer        user_data)
{
	g_return_if_fail (NAUTILUS_IS_WINDOW (window));

	nautilus_window_slot_open_location_full (nautilus_window_get_active_slot (window),
						 location, 0, NULL, callback, user_data);
}
