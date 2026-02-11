intel_lpm_suspend(struct hci_uart *hu)
{
	static const u8 suspend[] = { 0x01, 0x01, 0x01 };
	struct intel_data *intel = hu->priv;
	struct sk_buff *skb;

	if (!test_bit(STATE_LPM_ENABLED, &intel->flags) ||
	    test_bit(STATE_SUSPENDED, &intel->flags))
		return 0;

	if (test_bit(STATE_TX_ACTIVE, &intel->flags))
		return -EAGAIN;

	bt_dev_dbg(hu->hdev, "Suspending");

	skb = bt_skb_alloc(sizeof(suspend), GFP_KERNEL);
	if (!skb) {
		bt_dev_err(hu->hdev, "Failed to alloc memory for LPM packet");
		return -ENOMEM;
	}

	memcpy(skb_put(skb, sizeof(suspend)), suspend, sizeof(suspend));
	bt_cb(skb)->pkt_type = HCI_LPM_PKT;

	set_bit(STATE_LPM_TRANSACTION, &intel->flags);


	skb_queue_head(&intel->txq, skb);
	hci_uart_tx_wakeup(hu);

	intel_wait_lpm_transaction(hu);


	clear_bit(STATE_LPM_TRANSACTION, &intel->flags);

	if (!test_bit(STATE_SUSPENDED, &intel->flags)) {
		bt_dev_err(hu->hdev, "Device suspend error");
		return -EINVAL;
	}

	bt_dev_dbg(hu->hdev, "Suspended");

	hci_uart_set_flow_control(hu, true);

	return 0;
}
