gnome_scan_plugin_params_get_groups (GnomeScanPlugin *plugin)
{
	GSList* groups = NULL;
	GList* node = gnome_scan_plugin_get_params(plugin);
	GQuark cur_group = 0, last_group = 0;

	for (; node ; node = node->next) {
		cur_group = gs_param_spec_get_group (node->data);
		if (!last_group || last_group != cur_group) {
			groups = g_slist_append (groups, (gpointer) cur_group);
			last_group = cur_group;
		}
	}

	return groups;
}
