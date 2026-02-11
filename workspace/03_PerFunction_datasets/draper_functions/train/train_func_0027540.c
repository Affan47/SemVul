iface_build_net_config(struct iface_rec *iface, int iface_all,
			   struct iovec *iovs)
{
	int num_found = 0, rc;
	struct iface_net_config net_config;

	log_debug(8, "In iface_build_net_config\n");

	net_config.primary = iface;
	net_config.iovs = iovs;
	net_config.count = 0;

	if (iface_all)
		rc = iface_for_each_iface(&net_config, 0, &num_found,
					  __iface_build_net_config);
	else
		rc = __iface_build_net_config(&net_config, iface);

	log_debug(8, "iface_build_net_config: rc = %d, count = %d\n",
		  rc, net_config.count);
	return net_config.count;
}
