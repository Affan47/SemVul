ql_eeh_close(struct net_device *ndev)
{
	int i;
	struct ql_adapter *qdev = netdev_priv(ndev);

	if (netif_carrier_ok(ndev)) {
		netif_carrier_off(ndev);
		netif_stop_queue(ndev);
	}


	del_timer_sync(&qdev->timer);
	ql_cancel_all_work_sync(qdev);

	for (i = 0; i < qdev->rss_ring_count; i++)
		netif_napi_del(&qdev->rx_ring[i].napi);

	clear_bit(QL_ADAPTER_UP, &qdev->flags);
	ql_tx_ring_clean(qdev);
	ql_free_rx_buffers(qdev);
	ql_release_adapter_resources(qdev);
}
