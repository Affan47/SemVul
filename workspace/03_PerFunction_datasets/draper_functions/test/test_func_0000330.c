ixgbe_close(struct net_device *netdev)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);

	ixgbe_ptp_stop(adapter);

	if (netif_device_present(netdev))
		ixgbe_close_suspend(adapter);

	ixgbe_fdir_filter_exit(adapter);

	ixgbe_release_hw_control(adapter);

	return 0;
}
