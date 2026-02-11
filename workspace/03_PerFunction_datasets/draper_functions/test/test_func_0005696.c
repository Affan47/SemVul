xmms_xform_plugin_supports (const xmms_xform_plugin_t *plugin, xmms_stream_type_t *st,
                            gint *priority)
{
	GList *t;

	g_return_val_if_fail (st, FALSE);
	g_return_val_if_fail (plugin, FALSE);
	g_return_val_if_fail (priority, FALSE);

	for (t = plugin->in_types; t; t = g_list_next (t)) {
		xmms_config_property_t *config_priority;
		const gchar *type_name;
		gchar *config_key;

		if (!xmms_stream_type_match (t->data, st)) {
			continue;
		}

		type_name = xmms_stream_type_get_str (t->data, XMMS_STREAM_TYPE_NAME);

		config_key = g_strconcat ("priority.", type_name, NULL);
		config_priority = xmms_plugin_config_lookup ((xmms_plugin_t *) plugin,
		                                             config_key);
		g_free (config_key);

		if (config_priority) {
			*priority = xmms_config_property_get_int (config_priority);
		} else {
			*priority = XMMS_STREAM_TYPE_PRIORITY_DEFAULT;
		}

		return TRUE;
	}

	return FALSE;
}
