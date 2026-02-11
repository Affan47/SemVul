upnp_monitor_natpmp_callback(bool ok, natpmp_t *gateway, void *unused_arg)
{
	(void) unused_arg;

	gw.discovery_done = TRUE;

	if (!ok) {


		if (GNET_PROPERTY(upnp_debug) && gw.gateway != NULL) {
			g_warning("UPNP gateway %s failed its NAT-PMP health check",
				host_addr_to_string(natpmp_gateway_addr(gw.gateway)));
		}

		goto rediscover;
	} else {
		host_addr_t wan_ip;

		g_assert(gateway != NULL);
		g_assert(gw.gateway == gateway);

		wan_ip = natpmp_wan_ip(gateway);


		if (host_addr_is_routable(wan_ip)) {
			upnp_check_new_wan_addr(wan_ip);

			if (GNET_PROPERTY(upnp_debug) > 5) {
				g_debug("UPNP gateway %s still alive, WAN IP %s",
					host_addr_to_string(natpmp_gateway_addr(gateway)),
					host_addr_to_string2(wan_ip));
			}
		} else {
			if (GNET_PROPERTY(upnp_debug)) {
				g_warning("UPNP gateway %s reports unroutable WAN IP %s",
					host_addr_to_string(natpmp_gateway_addr(gateway)),
					host_addr_to_string2(wan_ip));
			}
			goto rediscover;
		}
	}


	g_assert(gateway != NULL);

	if (natpmp_has_rebooted(gateway)) {
		natpmp_clear_rebooted(gateway);
		upnp_map_publish_all();
	}

	return;

rediscover:


	gnet_prop_set_boolean_val(PROP_NATPMP_POSSIBLE, FALSE);
	gnet_prop_set_boolean_val(PROP_PORT_MAPPING_POSSIBLE, igd.dev != NULL);

	natpmp_free_null(&gw.gateway);
	gw.discover = TRUE;
}
