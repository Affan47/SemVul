nautilus_window_slot_set_viewed_file (NautilusWindowSlot *slot,
				      NautilusFile *file)
{
	NautilusFileAttributes attributes;

	if (slot->details->viewed_file == file) {
		return;
	}

	nautilus_file_ref (file);

	if (slot->details->viewed_file != NULL) {
		g_signal_handlers_disconnect_by_func (slot->details->viewed_file,
						      G_CALLBACK (viewed_file_changed_callback),
						      slot);
		nautilus_file_monitor_remove (slot->details->viewed_file,
					      slot);
	}

	if (file != NULL) {
		attributes =
			NAUTILUS_FILE_ATTRIBUTE_INFO |
			NAUTILUS_FILE_ATTRIBUTE_LINK_INFO;
		nautilus_file_monitor_add (file, slot, attributes);

		g_signal_connect_object (file, "changed",
					 G_CALLBACK (viewed_file_changed_callback), slot, 0);
	}

	nautilus_file_unref (slot->details->viewed_file);
	slot->details->viewed_file = file;
}
