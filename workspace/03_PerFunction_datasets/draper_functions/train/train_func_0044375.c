nautilus_directory_finalize (GObject *object)
{
	NautilusDirectory *directory;

	directory = NAUTILUS_DIRECTORY (object);

	g_hash_table_remove (directories, directory->details->location);

	nautilus_directory_cancel (directory);
	g_assert (directory->details->count_in_progress == NULL);
	g_assert (directory->details->top_left_read_state == NULL);

	if (directory->details->monitor_list != NULL) {
		g_warning ("destroying a NautilusDirectory while it's being monitored");
		g_list_free_full (directory->details->monitor_list, g_free);
	}

	if (directory->details->monitor != NULL) {
		nautilus_monitor_cancel (directory->details->monitor);
	}

	if (directory->details->dequeue_pending_idle_id != 0) {
		g_source_remove (directory->details->dequeue_pending_idle_id);
	}

	if (directory->details->call_ready_idle_id != 0) {
		g_source_remove (directory->details->call_ready_idle_id);
	}

	if (directory->details->location) {
		g_object_unref (directory->details->location);
	}

	g_assert (directory->details->file_list == NULL);
	g_hash_table_destroy (directory->details->file_hash);

	nautilus_file_queue_destroy (directory->details->high_priority_queue);
	nautilus_file_queue_destroy (directory->details->low_priority_queue);
	nautilus_file_queue_destroy (directory->details->extension_queue);
	g_assert (directory->details->directory_load_in_progress == NULL);
	g_assert (directory->details->count_in_progress == NULL);
	g_assert (directory->details->dequeue_pending_idle_id == 0);
	g_list_free_full (directory->details->pending_file_info, g_object_unref);

	G_OBJECT_CLASS (nautilus_directory_parent_class)->finalize (object);
}
