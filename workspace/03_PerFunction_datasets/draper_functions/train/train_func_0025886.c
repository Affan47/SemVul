on_scan_update_buffer_end (SymbolDBEngine * dbe, gint process_id, gpointer data)
{
	GPtrArray *files_to_scan;
	gint i;

	g_return_if_fail (dbe != NULL);
	g_return_if_fail (data != NULL);

	files_to_scan = (GPtrArray *) data;

	for (i = 0; i < files_to_scan->len; i++)
	{
		gchar *node = (gchar *) g_ptr_array_index (files_to_scan, i);
		const gchar *relative_path = symbol_db_util_get_file_db_path (dbe, node);
		if (relative_path != NULL)
		{

			if (sdb_engine_update_file (dbe, relative_path) == FALSE)
			{
				g_warning ("Error processing file %s", node);
				return;
			}
		}
	}

	g_signal_handlers_disconnect_by_func (dbe, on_scan_update_buffer_end,
										  files_to_scan);


	g_ptr_array_unref (files_to_scan);
	data = files_to_scan = NULL;
}
