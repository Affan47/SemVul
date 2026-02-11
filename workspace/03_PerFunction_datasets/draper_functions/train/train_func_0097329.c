plugin_db_catalog_save ( GWDBContext *context) {
	_data *data = NULL;
	gint result = -1;


	if ( context != NULL) {
		data = gw_db_context_get_data ( context);
		if ( gw_db_catalog_is_modified ( data->catalog) ) {
			result = csv_file_save ( context);
		} else {}
	} else {}

	return result;
}
