nautilus_window_sync_allow_stop (NautilusWindow *window,
				 NautilusWindowSlot *slot)
{
	GtkAction *stop_action;
	GtkAction *reload_action;
	gboolean allow_stop, slot_is_active, slot_allow_stop;

	stop_action = gtk_action_group_get_action (nautilus_window_get_main_action_group (window),
						   NAUTILUS_ACTION_STOP);
	reload_action = gtk_action_group_get_action (nautilus_window_get_main_action_group (window),
						     NAUTILUS_ACTION_RELOAD);
	allow_stop = gtk_action_get_sensitive (stop_action);

	slot_allow_stop = nautilus_window_slot_get_allow_stop (slot);
	slot_is_active = (slot == nautilus_window_get_active_slot (window));

	if (!slot_is_active ||
	    allow_stop != slot_allow_stop) {
		if (slot_is_active) {
			gtk_action_set_visible (stop_action, slot_allow_stop);
			gtk_action_set_visible (reload_action, !slot_allow_stop);
		}

		if (gtk_widget_get_realized (GTK_WIDGET (window))) {
			update_cursor (window);
		}

		nautilus_notebook_sync_loading (NAUTILUS_NOTEBOOK (window->details->notebook), slot);
	}
}
