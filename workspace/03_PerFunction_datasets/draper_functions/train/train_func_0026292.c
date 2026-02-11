upnp_service_cannot(upnp_service_t *usd, const char *action)
{
	upnp_service_check(usd);

	if (usd->api != NULL) {
		if (GNET_PROPERTY(upnp_debug)) {
			g_carp("UPNP %s if not really supporting %s()",
				upnp_service_to_string(usd), action);
		}

		nv_table_remove(usd->api, action);
	}
}
