on_project_loaded (IAnjutaProjectManager *pm, GError *error,
						  SymbolDBPlugin *sdb_plugin)
{
	g_return_if_fail (sdb_plugin->project_root_uri != NULL);
	g_return_if_fail (sdb_plugin->project_root_dir != NULL);


	if (error != NULL) return;


	if (sdb_plugin->needs_sources_scan == TRUE)
	{
		DEBUG_PRINT ("Importing sources.");
		do_import_project_sources (sdb_plugin, pm, sdb_plugin->project_root_dir);
	}
	else
	{


		GPtrArray *sources_array = NULL;

		DEBUG_PRINT ("Checking for files with zero symbols.");
		sources_array =
			symbol_db_util_get_files_with_zero_symbols (sdb_plugin->sdbe_project);

		if (sources_array != NULL && sources_array->len > 0)
		{
			DEBUG_PRINT ("Importing files after abort.");
			do_import_project_sources_after_abort (sdb_plugin, sources_array);

			g_ptr_array_unref (sources_array);
		}

		DEBUG_PRINT ("Checking for offline changes.");

		if (do_check_offline_files_changed (sdb_plugin) == FALSE)
		{
			DEBUG_PRINT ("no changes. Skipping.");
		}

		DEBUG_PRINT ("Updating project symbols.");

		if (do_update_project_symbols (sdb_plugin, sdb_plugin->project_opened) == FALSE)
		{
			DEBUG_PRINT ("no changes. Skipping.");
		}
	}
}
