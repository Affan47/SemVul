nautilus_window_slot_dispose (GObject *object)
{
	NautilusWindowSlot *slot;
	GtkWidget *widget;

	slot = NAUTILUS_WINDOW_SLOT (object);

	isearch_dispose (slot);

	nautilus_window_slot_clear_forward_list (slot);
	nautilus_window_slot_clear_back_list (slot);

	nautilus_window_slot_remove_extra_location_widgets (slot);

	if (slot->details->content_view) {
		nautilus_window_disconnect_content_view (nautilus_window_slot_get_window (slot),
							 slot->details->content_view);

		widget = GTK_WIDGET (slot->details->content_view);
		gtk_widget_destroy (widget);
		g_object_unref (slot->details->content_view);
		slot->details->content_view = NULL;
	}

	if (slot->details->new_content_view) {
		widget = GTK_WIDGET (slot->details->new_content_view);
		gtk_widget_destroy (widget);
		g_object_unref (slot->details->new_content_view);
		slot->details->new_content_view = NULL;
	}

	if (slot->details->set_status_timeout_id != 0) {
		g_source_remove (slot->details->set_status_timeout_id);
		slot->details->set_status_timeout_id = 0;
	}

	if (slot->details->loading_timeout_id != 0) {
		g_source_remove (slot->details->loading_timeout_id);
		slot->details->loading_timeout_id = 0;
	}

	nautilus_window_slot_set_viewed_file (slot, NULL);


	nautilus_file_unref (slot->details->viewed_file);

	if (slot->details->location) {


		g_object_ref (slot->details->location);
	}

	g_list_free_full (slot->details->pending_selection, g_object_unref);
	slot->details->pending_selection = NULL;

	g_clear_object (&slot->details->current_location_bookmark);
	g_clear_object (&slot->details->last_location_bookmark);

	if (slot->details->find_mount_cancellable != NULL) {
		g_cancellable_cancel (slot->details->find_mount_cancellable);
		slot->details->find_mount_cancellable = NULL;
	}

	slot->details->window = NULL;

	g_free (slot->details->title);
	slot->details->title = NULL;

	free_location_change (slot);

	G_OBJECT_CLASS (nautilus_window_slot_parent_class)->dispose (object);
}
