ath10k_wmi_tlv_op_pull_scan_ev(struct ath10k *ar,
					  struct sk_buff *skb,
					  struct wmi_scan_ev_arg *arg)
{
	const void **tb;
	const struct wmi_scan_event *ev;
	int ret;

	tb = ath10k_wmi_tlv_parse_alloc(ar, skb->data, skb->len, GFP_ATOMIC);
	if (IS_ERR(tb)) {
		ret = PTR_ERR(tb);
		ath10k_warn(ar, "failed to parse tlv: %d\n", ret);
		return ret;
	}

	ev = tb[WMI_TLV_TAG_STRUCT_SCAN_EVENT];
	if (!ev) {
		kfree(tb);
		return -EPROTO;
	}

	arg->event_type = ev->event_type;
	arg->reason = ev->reason;
	arg->channel_freq = ev->channel_freq;
	arg->scan_req_id = ev->scan_req_id;
	arg->scan_id = ev->scan_id;
	arg->vdev_id = ev->vdev_id;

	kfree(tb);
	return 0;
}
