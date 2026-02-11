igb_free_all_rx_resources(struct igb_adapter *adapter)
{
	int i;

	for (i = 0; i < adapter->num_rx_queues; i++)
		if (adapter->rx_ring[i])
			igb_free_rx_resources(adapter->rx_ring[i]);
}
