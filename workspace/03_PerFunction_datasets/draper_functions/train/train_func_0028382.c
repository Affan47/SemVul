interfaces_helper_chassis(struct lldpd *cfg,
    struct interfaces_device_list *interfaces)
{
	struct interfaces_device *iface;
	struct lldpd_hardware *hardware;
	char *name = NULL;

	LOCAL_CHASSIS(cfg)->c_cap_enabled &=
			    ~(LLDP_CAP_BRIDGE | LLDP_CAP_WLAN | LLDP_CAP_STATION);
	TAILQ_FOREACH(iface, interfaces, next) {
		if (iface->type & IFACE_BRIDGE_T)
			LOCAL_CHASSIS(cfg)->c_cap_enabled |= LLDP_CAP_BRIDGE;
		if (iface->type & IFACE_WIRELESS_T)
			LOCAL_CHASSIS(cfg)->c_cap_enabled |= LLDP_CAP_WLAN;
	}
	if ((LOCAL_CHASSIS(cfg)->c_cap_available & LLDP_CAP_STATION) &&
		(LOCAL_CHASSIS(cfg)->c_cap_enabled == 0))
	    LOCAL_CHASSIS(cfg)->c_cap_enabled = LLDP_CAP_STATION;

	if (LOCAL_CHASSIS(cfg)->c_id != NULL &&
	    LOCAL_CHASSIS(cfg)->c_id_subtype == LLDP_CHASSISID_SUBTYPE_LLADDR)
		return;

	TAILQ_FOREACH(iface, interfaces, next) {
		if (!(iface->type & IFACE_PHYSICAL_T)) continue;
		if (cfg->g_config.c_cid_pattern &&
		    !pattern_match(iface->name, cfg->g_config.c_cid_pattern, 0)) continue;

		if ((hardware = lldpd_get_hardware(cfg,
			    iface->name,
			    iface->index,
			    NULL)) == NULL)

			continue;

		name = malloc(ETHER_ADDR_LEN);
		if (!name) {
			log_warn("interfaces", "not enough memory for chassis ID");
			return;
		}
		free(LOCAL_CHASSIS(cfg)->c_id);
		memcpy(name, hardware->h_lladdr, ETHER_ADDR_LEN);
		LOCAL_CHASSIS(cfg)->c_id = name;
		LOCAL_CHASSIS(cfg)->c_id_len = ETHER_ADDR_LEN;
		LOCAL_CHASSIS(cfg)->c_id_subtype = LLDP_CHASSISID_SUBTYPE_LLADDR;
		return;
	}
}
