gda_config_get_provider_info (const gchar *provider_name)
{
	GSList *list;
	g_return_val_if_fail (provider_name, NULL);
	GDA_CONFIG_LOCK ();
	if (!unique_instance)
		gda_config_get ();

	if (!unique_instance->priv->providers_loaded)
		load_all_providers ();

	if (!g_ascii_strcasecmp (provider_name, "MS Access")) {
		GDA_CONFIG_UNLOCK ();
		return gda_config_get_provider_info ("MSAccess");
	}

	for (list = unique_instance->priv->prov_list; list; list = list->next)
		if (!g_ascii_strcasecmp (((GdaProviderInfo*) list->data)->id, provider_name)) {
			GDA_CONFIG_UNLOCK ();
			return (GdaProviderInfo*) list->data;
		}
	GDA_CONFIG_UNLOCK ();
	return NULL;
}
