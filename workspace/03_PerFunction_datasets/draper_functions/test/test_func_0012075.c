xkl_restore_names_prop(XklEngine * engine)
{
	gboolean rv = TRUE;
	gchar *rf = NULL;
	XklConfigRec *data = xkl_config_rec_new();

	if (!xkl_config_rec_get_from_root_window_property
	    (data, xkl_engine_priv(engine, backup_config_atom), NULL,
	     engine)) {
		g_object_unref(G_OBJECT(data));
		return FALSE;
	}

	if (!xkl_config_rec_set_to_root_window_property
	    (data, xkl_engine_priv(engine, base_config_atom), rf,
	     engine)) {
		xkl_debug(150, "Could not backup the configuration");
		rv = FALSE;
	}
	g_object_unref(G_OBJECT(data));
	return rv;
}
