gw_am_get_settings_tolx ( const gchar *name, const gint value) {
	gint result = -1;


	if ( (result = gw_am_get_settings_tol ( name)) == -1) {
		result = value;
	}

	return result;
}
