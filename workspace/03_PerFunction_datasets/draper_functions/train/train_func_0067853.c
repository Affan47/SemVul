ixgb_change_mtu(struct net_device *netdev, int new_mtu)
{
	struct ixgb_adapter *adapter = netdev_priv(netdev);
	int max_frame = new_mtu + ENET_HEADER_SIZE + ENET_FCS_LENGTH;
	int old_max_frame = netdev->mtu + ENET_HEADER_SIZE + ENET_FCS_LENGTH;


	if ((new_mtu < 68) ||
	    (max_frame > IXGB_MAX_JUMBO_FRAME_SIZE + ENET_FCS_LENGTH)) {
		netif_err(adapter, probe, adapter->netdev,
			  "Invalid MTU setting %d\n", new_mtu);
		return -EINVAL;
	}

	if (old_max_frame == max_frame)
		return 0;

	if (netif_running(netdev))
		ixgb_down(adapter, true);

	adapter->rx_buffer_len = max_frame + 8;

	netdev->mtu = new_mtu;

	if (netif_running(netdev))
		ixgb_up(adapter);

	return 0;
}
