e1000_intr(int irq, void *data)
{
	struct net_device *netdev = data;
	struct e1000_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;
	u32 icr = er32(ICR);

	if (unlikely((!icr)))
		return IRQ_NONE;


	if (unlikely(test_bit(__E1000_DOWN, &adapter->flags)))
		return IRQ_HANDLED;

	if (unlikely(icr & (E1000_ICR_RXSEQ | E1000_ICR_LSC))) {
		hw->get_link_status = 1;

		if (!test_bit(__E1000_DOWN, &adapter->flags))
			schedule_delayed_work(&adapter->watchdog_task, 1);
	}


	ew32(IMC, ~0);
	E1000_WRITE_FLUSH();

	if (likely(napi_schedule_prep(&adapter->napi))) {
		adapter->total_tx_bytes = 0;
		adapter->total_tx_packets = 0;
		adapter->total_rx_bytes = 0;
		adapter->total_rx_packets = 0;
		__napi_schedule(&adapter->napi);
	} else {


		if (!test_bit(__E1000_DOWN, &adapter->flags))
			e1000_irq_enable(adapter);
	}

	return IRQ_HANDLED;
}
