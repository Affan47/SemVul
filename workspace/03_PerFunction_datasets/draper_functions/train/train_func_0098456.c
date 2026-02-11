gw_helper_db_disk_name_is_exist ( GWDBContext *context, gchar *name) {
	GWCatalogPlugin *plugin = NULL;
	gboolean exist = FALSE;
	GWDBDisk **disks = NULL;
	gint i = 0;


	if ( context != NULL && name != NULL) {
		if ( (plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context)) != NULL) {
			if ( (disks = plugin->gw_db_catalog_get_db_disks ( context)) != NULL) {
				for ( i = 0; disks[i] != NULL; i++) {
					if ( !exist && strcmp ( name, gw_db_disk_get_name (disks[i])) == 0) {
						exist = TRUE;
					}

					gw_db_disk_free ( disks[i]);
				}

				g_free ( disks);
			}
		}
	}

	return exist;
}
