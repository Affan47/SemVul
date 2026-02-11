__qlcnic_set_multi(struct net_device *netdev, u16 vlan)
{
	struct qlcnic_adapter *adapter = netdev_priv(netdev);
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	struct netdev_hw_addr *ha;
	static const u8 bcast_addr[ETH_ALEN] = {
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff
	};
	u32 mode = VPORT_MISS_MODE_DROP;

	if (!test_bit(__QLCNIC_FW_ATTACHED, &adapter->state))
		return;

	qlcnic_nic_add_mac(adapter, adapter->mac_addr, vlan,
			   QLCNIC_UNICAST_MAC);
	qlcnic_nic_add_mac(adapter, bcast_addr, vlan, QLCNIC_BROADCAST_MAC);

	if (netdev->flags & IFF_PROMISC) {
		if (!(adapter->flags & QLCNIC_PROMISC_DISABLED))
			mode = VPORT_MISS_MODE_ACCEPT_ALL;
	} else if ((netdev->flags & IFF_ALLMULTI) ||
		   (netdev_mc_count(netdev) > ahw->max_mc_count)) {
		mode = VPORT_MISS_MODE_ACCEPT_MULTI;
	} else if (!netdev_mc_empty(netdev)) {
		qlcnic_flush_mcast_mac(adapter);
		netdev_for_each_mc_addr(ha, netdev)
			qlcnic_nic_add_mac(adapter, ha->addr, vlan,
					   QLCNIC_MULTICAST_MAC);
	}


	if (netdev_uc_count(netdev) > ahw->max_uc_count) {
		mode = VPORT_MISS_MODE_ACCEPT_ALL;
	} else if (!netdev_uc_empty(netdev)) {
		netdev_for_each_uc_addr(ha, netdev)
			qlcnic_nic_add_mac(adapter, ha->addr, vlan,
					   QLCNIC_UNICAST_MAC);
	}

	if (mode == VPORT_MISS_MODE_ACCEPT_ALL &&
	    !adapter->fdb_mac_learn) {
		qlcnic_alloc_lb_filters_mem(adapter);
		adapter->drv_mac_learn = 1;
		if (adapter->flags & QLCNIC_ESWITCH_ENABLED)
			adapter->rx_mac_learn = true;
	} else {
		adapter->drv_mac_learn = 0;
		adapter->rx_mac_learn = false;
	}

	qlcnic_nic_set_promisc(adapter, mode);
}
