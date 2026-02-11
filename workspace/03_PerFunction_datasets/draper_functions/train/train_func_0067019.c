intel_dequeue(struct hci_uart *hu)
{
	struct intel_data *intel = hu->priv;
	struct sk_buff *skb;

	skb = skb_dequeue(&intel->txq);
	if (!skb)
		return skb;

	if (test_bit(STATE_BOOTLOADER, &intel->flags) &&
	    (bt_cb(skb)->pkt_type == HCI_COMMAND_PKT)) {
		struct hci_command_hdr *cmd = (void *)skb->data;
		__u16 opcode = le16_to_cpu(cmd->opcode);


		if (opcode == 0xfc01)
			inject_cmd_complete(hu->hdev, opcode);
	}


	memcpy(skb_push(skb, 1), &bt_cb(skb)->pkt_type, 1);

	return skb;
}
