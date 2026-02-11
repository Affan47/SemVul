merged_call_when_ready (NemoDirectory *directory,
			NemoFileAttributes file_attributes,
			gboolean wait_for_file_list,
			NemoDirectoryCallback callback,
			gpointer callback_data)
{
	NemoMergedDirectory *merged;
	MergedCallback search_key, *merged_callback;
	GList *node;

	merged = NEMO_MERGED_DIRECTORY (directory);


	search_key.callback = callback;
	search_key.callback_data = callback_data;
	if (g_hash_table_lookup (merged->details->callbacks, &search_key) != NULL) {
		g_warning ("tried to add a new callback while an old one was pending");
		return;
	}


	merged_callback = g_new0 (MergedCallback, 1);
	merged_callback->merged = merged;
	merged_callback->callback = callback;
	merged_callback->callback_data = callback_data;
	merged_callback->wait_for_attributes = file_attributes;
	merged_callback->wait_for_file_list = wait_for_file_list;
	for (node = merged->details->directories; node != NULL; node = node->next) {
		merged_callback->non_ready_directories = g_list_prepend
			(merged_callback->non_ready_directories, node->data);
	}


	g_hash_table_insert (merged->details->callbacks,
			     merged_callback, merged_callback);


	if (merged->details->directories == NULL) {
		merged_callback_check_done (merged_callback);
	}


	for (node = merged->details->directories; node != NULL; node = node->next) {
		nemo_directory_call_when_ready
			(node->data,
			 merged_callback->wait_for_attributes,
			 merged_callback->wait_for_file_list,
			 directory_ready_callback, merged_callback);
	}
}
