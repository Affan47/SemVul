nautilus_window_slot_update_title (NautilusWindowSlot *slot)
{
	NautilusWindow *window;
	char *title;
	gboolean do_sync = FALSE;

	title = nautilus_compute_title_for_location (slot->details->location);
	window = nautilus_window_slot_get_window (slot);

	if (g_strcmp0 (title, slot->details->title) != 0) {
		do_sync = TRUE;

		g_free (slot->details->title);
		slot->details->title = title;
		title = NULL;
	}

	if (strlen (slot->details->title) > 0) {
		do_sync = TRUE;
	}

	if (do_sync) {
		nautilus_window_sync_title (window, slot);
	}

	if (title != NULL) {
		g_free (title);
	}
}
