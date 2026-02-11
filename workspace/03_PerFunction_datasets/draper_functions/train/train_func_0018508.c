directory_load_done (NemoDirectory *directory,
		     GError *error)
{
	GList *node;

	directory->details->directory_loaded = TRUE;
	directory->details->directory_loaded_sent_notification = FALSE;

	if (error != NULL) {


		for (node = directory->details->file_list;
		     node != NULL; node = node->next) {
			set_file_unconfirmed (NEMO_FILE (node->data), FALSE);
		}

		nemo_directory_emit_load_error (directory, error);
	}


	if (directory->details->dequeue_pending_idle_id != 0) {
		g_source_remove (directory->details->dequeue_pending_idle_id);
	}
	dequeue_pending_idle_callback (directory);

	directory_load_cancel (directory);
}
