ixgbe_set_num_queues(struct ixgbe_adapter *adapter)
{

	adapter->num_rx_queues = 1;
	adapter->num_tx_queues = 1;
	adapter->num_rx_pools = adapter->num_rx_queues;
	adapter->num_rx_queues_per_pool = 1;

#ifdef CONFIG_IXGBE_DCB
	if (ixgbe_set_dcb_sriov_queues(adapter))
		return;

	if (ixgbe_set_dcb_queues(adapter))
		return;

#endif
	if (ixgbe_set_sriov_queues(adapter))
		return;

	ixgbe_set_rss_queues(adapter);
}
