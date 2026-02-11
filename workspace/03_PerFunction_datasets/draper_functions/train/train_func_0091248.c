ath10k_wmi_tlv_event_diag(struct ath10k *ar,
				     struct sk_buff *skb)
{
	const void **tb;
	const void *data;
	int ret, len;

	tb = ath10k_wmi_tlv_parse_alloc(ar, skb->data, skb->len, GFP_ATOMIC);
	if (IS_ERR(tb)) {
		ret = PTR_ERR(tb);
		ath10k_warn(ar, "failed to parse tlv: %d\n", ret);
		return ret;
	}

	data = tb[WMI_TLV_TAG_ARRAY_BYTE];
	if (!data) {
		kfree(tb);
		return -EPROTO;
	}
	len = ath10k_wmi_tlv_len(data);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv diag event len %d\n", len);
	trace_ath10k_wmi_diag(ar, data, len);

	kfree(tb);
	return 0;
}
