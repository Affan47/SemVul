on_update_indicators_idle (gpointer data)
{
	BasicAutotoolsPlugin *ba_plugin = ANJUTA_PLUGIN_BASIC_AUTOTOOLS (data);
	IAnjutaEditor *editor = ba_plugin->current_editor;


	if (ba_plugin->current_editor_file &&
		IANJUTA_IS_INDICABLE (editor) &&
		g_settings_get_boolean (ba_plugin->settings,
		                        PREF_INDICATORS_AUTOMATIC))
	{
		GList *node;
		node = ba_plugin->contexts_pool;
		while (node)
		{
			BuildContext *context = node->data;
			if (g_hash_table_lookup (context->indicators_updated_editors,
									 editor) == NULL)
			{
				GSList *loc_node;
				ianjuta_indicable_clear (IANJUTA_INDICABLE (editor), NULL);


				loc_node = context->locations;
				while (loc_node)
				{
					build_indicator_location_set ((BuildIndicatorLocation*) loc_node->data,
					IANJUTA_EDITOR (editor), ba_plugin->current_editor_file);
					loc_node = g_slist_next (loc_node);
				}
				g_hash_table_insert (context->indicators_updated_editors,
									 editor, editor);
			}
			node = g_list_next (node);
		}
	}

	ba_plugin->update_indicators_idle = 0;
	return FALSE;
}
