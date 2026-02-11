e1000_intr_msix_rx(int __always_unused irq, void *data)
{
	struct net_device *netdev = data;
	struct e1000_adapter *adapter = netdev_priv(netdev);
	struct e1000_ring *rx_ring = adapter->rx_ring;


	if (rx_ring->set_itr) {
		u32 itr = rx_ring->itr_val ?
			  1000000000 / (rx_ring->itr_val * 256) : 0;

		writel(itr, rx_ring->itr_register);
		rx_ring->set_itr = 0;
	}

	if (napi_schedule_prep(&adapter->napi)) {
		adapter->total_rx_bytes = 0;
		adapter->total_rx_packets = 0;
		__napi_schedule(&adapter->napi);
	}
	return IRQ_HANDLED;
}
