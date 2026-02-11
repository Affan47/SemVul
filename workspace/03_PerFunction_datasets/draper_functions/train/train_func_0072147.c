dht_initiate_bootstrap(void)
{
	if (dht_is_bootstrapping()) {
		if (GNET_PROPERTY(dht_debug))
			g_debug("DHT already bootstrapping, ignoring request to bootstrap");
		return;
	}

	if (GNET_PROPERTY(dht_debug))
		g_debug("DHT attempting bootstrap -- looking for our own KUID");


	if (!lookup_find_node(our_kuid, NULL, bootstrap_status, NULL)) {
		if (GNET_PROPERTY(dht_debug))
			g_debug("DHT bootstrapping impossible: routing table empty");

		gnet_prop_set_guint32_val(PROP_DHT_BOOT_STATUS, DHT_BOOT_NONE);
	} else {
		gnet_prop_set_guint32_val(PROP_DHT_BOOT_STATUS, DHT_BOOT_OWN);
	}
}
