show_query_editor (NautilusWindowSlot *slot)
{
	NautilusDirectory *directory;
	NautilusSearchDirectory *search_directory;
	GFile *location;

	if (slot->details->location) {
		location = slot->details->location;
	} else {
		location = slot->details->pending_location;
	}

	directory = nautilus_directory_get (location);

	if (NAUTILUS_IS_SEARCH_DIRECTORY (directory)) {
		NautilusQuery *query;
		search_directory = NAUTILUS_SEARCH_DIRECTORY (directory);
		query = nautilus_search_directory_get_query (search_directory);
		if (query != NULL) {
			nautilus_query_editor_set_query (slot->details->query_editor,
							 query);
			g_object_unref (query);
		}
	} else {
		nautilus_query_editor_set_location (slot->details->query_editor, location);
	}

	nautilus_directory_unref (directory);

	gtk_revealer_set_reveal_child (GTK_REVEALER (slot->details->query_editor_revealer),
				       TRUE);
	gtk_widget_grab_focus (GTK_WIDGET (slot->details->query_editor));

	if (slot->details->qe_changed_id == 0) {
		slot->details->qe_changed_id =
			g_signal_connect (slot->details->query_editor, "changed",
					  G_CALLBACK (query_editor_changed_callback), slot);
	}
	if (slot->details->qe_cancel_id == 0) {
		slot->details->qe_cancel_id =
			g_signal_connect (slot->details->query_editor, "cancel",
					  G_CALLBACK (query_editor_cancel_callback), slot);
	}
	if (slot->details->qe_activated_id == 0) {
		slot->details->qe_activated_id =
			g_signal_connect (slot->details->query_editor, "activated",
					  G_CALLBACK (query_editor_activated_callback), slot);
	}
}
