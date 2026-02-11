__netxen_nic_up(struct netxen_adapter *adapter, struct net_device *netdev)
{
	int err;

	if (adapter->is_up != NETXEN_ADAPTER_UP_MAGIC)
		return -EIO;

	err = adapter->init_port(adapter, adapter->physical_port);
	if (err) {
		printk(KERN_ERR "%s: Failed to initialize port %d\n",
				netxen_nic_driver_name, adapter->portnum);
		return err;
	}
	if (NX_IS_REVISION_P2(adapter->ahw.revision_id))
		adapter->macaddr_set(adapter, adapter->mac_addr);

	adapter->set_multi(netdev);
	adapter->set_mtu(adapter, netdev->mtu);

	adapter->ahw.linkup = 0;

	if (adapter->max_sds_rings > 1)
		netxen_config_rss(adapter, 1);

	if (NX_IS_REVISION_P3(adapter->ahw.revision_id))
		netxen_config_intr_coalesce(adapter);

	if (netdev->features & NETIF_F_LRO)
		netxen_config_hw_lro(adapter, NETXEN_NIC_LRO_ENABLED);

	netxen_napi_enable(adapter);

	if (adapter->capabilities & NX_FW_CAPABILITY_LINK_NOTIFICATION)
		netxen_linkevent_request(adapter, 1);
	else
		netxen_nic_set_link_parameters(adapter);

	set_bit(__NX_DEV_UP, &adapter->state);
	return 0;
}
