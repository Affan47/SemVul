et131x_tx_timeout(struct net_device *netdev)
{
	struct et131x_adapter *adapter = netdev_priv(netdev);
	struct tx_ring *tx_ring = &adapter->tx_ring;
	struct tcb *tcb;
	unsigned long flags;


	if (~(adapter->flags & FMP_ADAPTER_INTERRUPT_IN_USE))
		return;


	if (adapter->flags & FMP_ADAPTER_NON_RECOVER_ERROR)
		return;


	if (adapter->flags & FMP_ADAPTER_HARDWARE_ERROR) {
		dev_err(&adapter->pdev->dev, "hardware error - reset\n");
		return;
	}


	spin_lock_irqsave(&adapter->tcb_send_qlock, flags);
	tcb = tx_ring->send_head;
	spin_unlock_irqrestore(&adapter->tcb_send_qlock, flags);

	if (tcb) {
		tcb->count++;

		if (tcb->count > NIC_SEND_HANG_THRESHOLD) {
			dev_warn(&adapter->pdev->dev,
				 "Send stuck - reset. tcb->WrIndex %x\n",
				 tcb->index);

			adapter->netdev->stats.tx_errors++;


			et131x_disable_txrx(netdev);
			et131x_enable_txrx(netdev);
		}
	}
}
