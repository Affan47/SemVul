next_iface(struct iface_info *info, int *err, struct iface_conf_list *ifaces) {
	if (next_iface4(info, err, ifaces)) {
		return 1;
	}
#ifdef DHCPv6
	if (!(*err)) {
		if (local_family == AF_INET6)
			return next_iface6(info, err, ifaces);
	}
#endif
	return 0;
}
