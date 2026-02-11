interfaces_update(struct lldpd *cfg)
{
	struct lldpd_hardware *hardware;
	struct interfaces_device_list *interfaces;
	struct interfaces_address_list *addresses;
	interfaces = netlink_get_interfaces();
	addresses = netlink_get_addresses();
	if (interfaces == NULL || addresses == NULL) {
		log_warnx("interfaces", "cannot update the list of local interfaces");
		goto end;
	}


	iflinux_add_driver(cfg, interfaces);
	if (LOCAL_CHASSIS(cfg)->c_cap_available & LLDP_CAP_WLAN)
		iflinux_add_wireless(cfg, interfaces);
	if (LOCAL_CHASSIS(cfg)->c_cap_available & LLDP_CAP_BRIDGE)
		iflinux_add_bridge(cfg, interfaces);
	iflinux_add_bond(cfg, interfaces);
	iflinux_add_vlan(cfg, interfaces);
	iflinux_add_physical(cfg, interfaces);

	interfaces_helper_whitelist(cfg, interfaces);
	iflinux_handle_bond(cfg, interfaces);
	interfaces_helper_physical(cfg, interfaces,
	    &eth_ops,
	    iflinux_eth_init);
#ifdef ENABLE_DOT1
	interfaces_helper_vlan(cfg, interfaces);
#endif
	interfaces_helper_mgmt(cfg, addresses);
	interfaces_helper_chassis(cfg, interfaces);


	TAILQ_FOREACH(hardware, &cfg->g_hardware, h_entries) {
		if (!hardware->h_flags) continue;
		iflinux_macphy(hardware);
		interfaces_helper_promisc(cfg, hardware);
	}

	if (cfg->g_iface_event == NULL) {
		int s;
		log_debug("interfaces", "subscribe to netlink notifications");
		s = netlink_subscribe_changes();
		if (s == -1) {
			log_warnx("interfaces", "unable to subscribe to netlink notifications");
			goto end;
		}
		if (levent_iface_subscribe(cfg, s) == -1)
			close(s);


	}

end:
	interfaces_free_devices(interfaces);
	interfaces_free_addresses(addresses);
}
