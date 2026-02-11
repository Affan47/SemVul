qlcnic_poll_controller(struct net_device *netdev)
{
	struct qlcnic_adapter *adapter = netdev_priv(netdev);
	struct qlcnic_host_sds_ring *sds_ring;
	struct qlcnic_recv_context *recv_ctx;
	struct qlcnic_host_tx_ring *tx_ring;
	int ring;

	if (!test_bit(__QLCNIC_DEV_UP, &adapter->state))
		return;

	recv_ctx = adapter->recv_ctx;

	for (ring = 0; ring < adapter->drv_sds_rings; ring++) {
		sds_ring = &recv_ctx->sds_rings[ring];
		qlcnic_disable_sds_intr(adapter, sds_ring);
		napi_schedule(&sds_ring->napi);
	}

	if (adapter->flags & QLCNIC_MSIX_ENABLED) {


		if ((qlcnic_83xx_check(adapter) &&
		     (adapter->flags & QLCNIC_TX_INTR_SHARED)) ||
		    (qlcnic_82xx_check(adapter) &&
		     !qlcnic_check_multi_tx(adapter)))
			return;

		for (ring = 0; ring < adapter->drv_tx_rings; ring++) {
			tx_ring = &adapter->tx_ring[ring];
			qlcnic_disable_tx_intr(adapter, tx_ring);
			napi_schedule(&tx_ring->napi);
		}
	}
}
