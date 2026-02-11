get_netvsc_byref(struct net_device *vf_netdev)
{
	struct net_device *dev;

	ASSERT_RTNL();

	for_each_netdev(&init_net, dev) {
		struct net_device_context *net_device_ctx;

		if (dev->netdev_ops != &device_ops)
			continue;

		net_device_ctx = netdev_priv(dev);
		if (net_device_ctx->nvdev == NULL)
			continue;

		if (rtnl_dereference(net_device_ctx->vf_netdev) == vf_netdev)
			return dev;
	}

	return NULL;
}
