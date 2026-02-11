bnx2x_set_channels(struct net_device *dev,
			      struct ethtool_channels *channels)
{
	struct bnx2x *bp = netdev_priv(dev);

	DP(BNX2X_MSG_ETHTOOL,
	   "set-channels command parameters: rx = %d, tx = %d, other = %d, combined = %d\n",
	   channels->rx_count, channels->tx_count, channels->other_count,
	   channels->combined_count);

	if (pci_num_vf(bp->pdev)) {
		DP(BNX2X_MSG_IOV, "VFs are enabled, can not set channels\n");
		return -EPERM;
	}


	if (channels->rx_count || channels->tx_count || channels->other_count
	    || (channels->combined_count == 0) ||
	    (channels->combined_count > BNX2X_MAX_RSS_COUNT(bp))) {
		DP(BNX2X_MSG_ETHTOOL, "command parameters not supported\n");
		return -EINVAL;
	}


	if (channels->combined_count == BNX2X_NUM_ETH_QUEUES(bp)) {
		DP(BNX2X_MSG_ETHTOOL, "No change in active parameters\n");
		return 0;
	}


	if (unlikely(!netif_running(dev))) {
		bnx2x_change_num_queues(bp, channels->combined_count);
		return 0;
	}
	bnx2x_nic_unload(bp, UNLOAD_NORMAL, true);
	bnx2x_change_num_queues(bp, channels->combined_count);
	return bnx2x_nic_load(bp, LOAD_NORMAL);
}
