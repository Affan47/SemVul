symbol_db_system_scan_package (SymbolDBSystem *sdbs,
							  const gchar * package_name)
{
	SingleScanData *ss_data;

	g_return_val_if_fail (sdbs != NULL, FALSE);
	g_return_val_if_fail (package_name != NULL, FALSE);


	if (symbol_db_system_is_package_parsed (sdbs, package_name, "1.0") == TRUE)
	{
		DEBUG_PRINT ("symbol_db_system_scan_package (): no need to scan %s",
					 package_name);
		return FALSE;
	}
	else
	{
		DEBUG_PRINT ("symbol_db_system_scan_package (): NEED to scan %s",
					 package_name);
	}


	ss_data = (SingleScanData*)g_new0 (SingleScanData, 1);


	ss_data->sdbs = sdbs;
	ss_data->package_name = g_strdup (package_name);
	ss_data->contents = NULL;
	ss_data->parseable_cb = NULL;
	ss_data->parseable_data = NULL;
	ss_data->engine_scan = TRUE;


	sdb_system_do_scan_new_package (sdbs, ss_data);
	return TRUE;
}
