upnp_monitor_igd_callback(int code, void *value, size_t size, void *unused_arg)
{
	struct upnp_GetExternalIPAddress *ret = value;

	(void) unused_arg;

	g_assert(NULL == value || size == sizeof *ret);

	igd.monitor = NULL;

	if (NULL == ret) {


		if (GNET_PROPERTY(upnp_debug) && igd.dev != NULL) {
			g_warning("UPNP device \"%s\" reports no external IP "
				"(error %d => \"%s\")",
				igd.dev->desc_url, code, upnp_strerror(code));
		}

		goto rediscover;
	} else if (igd.dev != NULL) {


		if (host_addr_is_routable(ret->external_ip)) {
			upnp_check_new_wan_addr(ret->external_ip);
			igd.dev->u.igd.wan_ip = ret->external_ip;

			if (GNET_PROPERTY(upnp_debug) > 5) {
				g_debug("UPNP device \"%s\" still alive, WAN IP %s",
					igd.dev->desc_url,
					host_addr_to_string(igd.dev->u.igd.wan_ip));
			}
		} else {
			if (GNET_PROPERTY(upnp_debug)) {
				g_warning("UPNP device \"%s\" reports unroutable WAN IP %s",
					igd.dev->desc_url, host_addr_to_string(ret->external_ip));
			}
			goto rediscover;
		}
	} else {
		return;
	}

	g_assert(igd.dev != NULL);


	{
		upnp_service_t *usd;


		usd = upnp_service_get_common_if(igd.dev->services);
		if (upnp_service_can(usd, UPNP_GET_TOTAL_RX_PACKETS)) {
			igd.monitor = upnp_ctrl_GetTotalPacketsReceived(usd,
					upnp_packets_igd_callback, NULL);
			goto done;
		}

		usd = upnp_service_get_wan_connection(igd.dev->services);
		if (upnp_service_can(usd, UPNP_GET_STATUS_INFO)) {
			igd.monitor = upnp_ctrl_GetStatusInfo(usd,
					upnp_status_igd_callback, NULL);
			goto done;
		}

		if (GNET_PROPERTY(upnp_debug)) {
			g_warning("UPNP cannot monitor device \"%s\", republishing",
				igd.dev->desc_url);
		}

		upnp_map_publish_all();
	}

done:
	return;

rediscover:


	gnet_prop_set_boolean_val(PROP_UPNP_POSSIBLE, FALSE);
	gnet_prop_set_boolean_val(PROP_PORT_MAPPING_POSSIBLE, gw.gateway != NULL);

	upnp_dev_free_null(&igd.dev);
	igd.discover = TRUE;
}
