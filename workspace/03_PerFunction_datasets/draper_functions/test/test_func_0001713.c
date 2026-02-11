ena_up_complete(struct ena_adapter *adapter)
{
	int rc, i;

	rc = ena_rss_configure(adapter);
	if (rc)
		return rc;

	ena_init_napi(adapter);

	ena_change_mtu(adapter->netdev, adapter->netdev->mtu);

	ena_refill_all_rx_bufs(adapter);


	netif_tx_start_all_queues(adapter->netdev);

	ena_restore_ethtool_params(adapter);

	ena_napi_enable_all(adapter);


	for (i = 0; i < adapter->num_queues; i++)
		napi_schedule(&adapter->ena_napi[i].napi);

	return 0;
}
