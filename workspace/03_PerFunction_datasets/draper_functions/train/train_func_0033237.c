i40evf_free_all_tx_resources(struct i40evf_adapter *adapter)
{
	int i;

	if (!adapter->tx_rings)
		return;

	for (i = 0; i < adapter->num_active_queues; i++)
		if (adapter->tx_rings[i].desc)
			i40evf_free_tx_resources(&adapter->tx_rings[i]);
}
