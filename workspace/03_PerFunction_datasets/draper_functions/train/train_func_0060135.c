gw_helper_db_disk_get_name ( GWDBContext *context, gchar *name) {
	gchar *tmp_name = NULL;
	gint i = 2;


#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	if ( context != NULL && name != NULL ) {
		tmp_name = g_strdup ( name);

		while ( gw_helper_db_disk_name_is_exist ( context, tmp_name) ) {
			g_free ( tmp_name);
			tmp_name = g_strdup_printf ( "%s (%d)", name, i++);
		}
	}

	return tmp_name;
}
