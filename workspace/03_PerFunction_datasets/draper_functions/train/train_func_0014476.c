intel_recv_lpm(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct hci_lpm_pkt *lpm = (void *)skb->data;
	struct hci_uart *hu = hci_get_drvdata(hdev);
	struct intel_data *intel = hu->priv;

	switch (lpm->opcode) {
	case LPM_OP_TX_NOTIFY:
		if (lpm->dlen < 1) {
			bt_dev_err(hu->hdev, "Invalid LPM notification packet");
			break;
		}
		intel_recv_lpm_notify(hdev, lpm->data[0]);
		break;
	case LPM_OP_SUSPEND_ACK:
		set_bit(STATE_SUSPENDED, &intel->flags);
		if (test_and_clear_bit(STATE_LPM_TRANSACTION, &intel->flags)) {
			smp_mb__after_atomic();
			wake_up_bit(&intel->flags, STATE_LPM_TRANSACTION);
		}
		break;
	case LPM_OP_RESUME_ACK:
		clear_bit(STATE_SUSPENDED, &intel->flags);
		if (test_and_clear_bit(STATE_LPM_TRANSACTION, &intel->flags)) {
			smp_mb__after_atomic();
			wake_up_bit(&intel->flags, STATE_LPM_TRANSACTION);
		}
		break;
	default:
		bt_dev_err(hdev, "Unknown LPM opcode (%02x)", lpm->opcode);
		break;
	}

	kfree_skb(skb);

	return 0;
}
