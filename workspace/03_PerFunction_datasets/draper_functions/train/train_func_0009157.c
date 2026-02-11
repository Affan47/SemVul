iflinux_add_bridge(struct lldpd *cfg,
    struct interfaces_device_list *interfaces)
{
	struct interfaces_device *iface;

	TAILQ_FOREACH(iface, interfaces, next) {
		if (iface->type & (IFACE_PHYSICAL_T|
			IFACE_VLAN_T|IFACE_BOND_T|IFACE_BRIDGE_T))
			continue;
		if (iflinux_is_bridge(cfg, interfaces, iface)) {
			log_debug("interfaces",
			    "interface %s is a bridge",
			    iface->name);
			iface->type |= IFACE_BRIDGE_T;
		}
	}
}
