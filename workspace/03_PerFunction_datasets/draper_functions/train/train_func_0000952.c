iflinux_add_physical(struct lldpd *cfg,
    struct interfaces_device_list *interfaces)
{
	struct interfaces_device *iface;

	const char * const *rif;
	const char * const regular_interfaces[] = {
		"dsa",
		"veth",
		NULL
	};

	TAILQ_FOREACH(iface, interfaces, next) {
		if (iface->type & (IFACE_VLAN_T|
			IFACE_BOND_T|IFACE_BRIDGE_T))
			continue;

		iface->type &= ~IFACE_PHYSICAL_T;


		if (!(iface->flags & (IFF_MULTICAST|IFF_BROADCAST))) {
			log_debug("interfaces", "skip %s: not able to do multicast nor broadcast",
			    iface->name);
			continue;
		}


		if (iface->driver) {
			for (rif = regular_interfaces; *rif; rif++) {
				if (strcmp(iface->driver, *rif) == 0) {

					log_debug("interfaces", "accept %s: whitelisted",
					    iface->name);
					iface->type |= IFACE_PHYSICAL_T;
					continue;
				}
			}
		}


		if (iface->lower) {
			log_debug("interfaces", "skip %s: there is a lower interface (%s)",
			    iface->name, iface->lower->name);
			continue;
		}


		if (iface->txqueue == 0) {
			log_debug("interfaces", "skip %s: no queue",
			    iface->name);
			continue;
		}


		iflinux_get_permanent_mac(cfg, interfaces, iface);

		log_debug("interfaces",
		    "%s is a physical interface",
		    iface->name);
		iface->type |= IFACE_PHYSICAL_T;
	}
}
