dump_skb(struct sk_buff *skb, struct qlcnic_adapter *adapter)
{
	if (adapter->ahw->msg_enable & NETIF_MSG_DRV) {
		char prefix[30];

		scnprintf(prefix, sizeof(prefix), "%s: %s: ",
			  dev_name(&adapter->pdev->dev), __func__);

		print_hex_dump_debug(prefix, DUMP_PREFIX_NONE, 16, 1,
				     skb->data, skb->len, true);
	}
}
