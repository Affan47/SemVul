netvsc_vf_up(struct net_device *vf_netdev)
{
	struct net_device *ndev;
	struct netvsc_device *netvsc_dev;
	struct net_device_context *net_device_ctx;

	ndev = get_netvsc_byref(vf_netdev);
	if (!ndev)
		return NOTIFY_DONE;

	net_device_ctx = netdev_priv(ndev);
	netvsc_dev = net_device_ctx->nvdev;

	netdev_info(ndev, "VF up: %s\n", vf_netdev->name);


	rndis_filter_open(netvsc_dev);


	netvsc_switch_datapath(ndev, true);
	netdev_info(ndev, "Data path switched to VF: %s\n", vf_netdev->name);

	netif_carrier_off(ndev);


	call_netdevice_notifiers(NETDEV_NOTIFY_PEERS, vf_netdev);

	return NOTIFY_OK;
}
