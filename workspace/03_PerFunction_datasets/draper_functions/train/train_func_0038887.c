unmanaged_specs_changed (NMSystemConfigInterface *config,
                         gpointer user_data)
{
	NMSettings *self = NM_SETTINGS (user_data);
	NMSettingsPrivate *priv = NM_SETTINGS_GET_PRIVATE (self);
	GSList *iter;

	clear_unmanaged_specs (self);


	for (iter = priv->plugins; iter; iter = g_slist_next (iter)) {
		GSList *specs, *specs_iter;

		specs = nm_system_config_interface_get_unmanaged_specs (NM_SYSTEM_CONFIG_INTERFACE (iter->data));
		for (specs_iter = specs; specs_iter; specs_iter = specs_iter->next) {
			if (!find_unmanaged_device (self, (const char *) specs_iter->data)) {
				priv->unmanaged_specs = g_slist_prepend (priv->unmanaged_specs, specs_iter->data);
			} else
				g_free (specs_iter->data);
		}

		g_slist_free (specs);
	}

	g_object_notify (G_OBJECT (self), NM_SETTINGS_UNMANAGED_SPECS);
}
