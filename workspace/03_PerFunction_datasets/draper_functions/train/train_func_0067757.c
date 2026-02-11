gc_master_provider_subscribe (GcMasterProvider *provider,
                              gpointer          client,
                              GcInterfaceFlags  interface)
{
	GcMasterProviderPrivate *priv = GET_PRIVATE (provider);
	gboolean started = FALSE;


	if (!gc_master_provider_is_running (provider)) {
		if (!(priv->provides & GEOCLUE_PROVIDE_CACHEABLE_ON_CONNECTION)) {
			started = gc_master_provider_initialize (provider);
		}
	}


	if (interface & GC_IFACE_POSITION) {
		if (!g_list_find (priv->position_clients, client)) {
			priv->position_clients = g_list_prepend (priv->position_clients, client);
		}
	}
	if (interface & GC_IFACE_ADDRESS) {
		if (!g_list_find (priv->address_clients, client)) {
			priv->address_clients = g_list_prepend (priv->address_clients, client);
		}
	}

	return started;
}
