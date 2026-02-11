ath10k_wmi_tlv_event_bcn_tx_status(struct ath10k *ar,
					      struct sk_buff *skb)
{
	const void **tb;
	const struct wmi_tlv_bcn_tx_status_ev *ev;
	struct ath10k_vif *arvif;
	u32 vdev_id, tx_status;
	int ret;

	tb = ath10k_wmi_tlv_parse_alloc(ar, skb->data, skb->len, GFP_ATOMIC);
	if (IS_ERR(tb)) {
		ret = PTR_ERR(tb);
		ath10k_warn(ar, "failed to parse tlv: %d\n", ret);
		return ret;
	}

	ev = tb[WMI_TLV_TAG_STRUCT_OFFLOAD_BCN_TX_STATUS_EVENT];
	if (!ev) {
		kfree(tb);
		return -EPROTO;
	}

	tx_status = __le32_to_cpu(ev->tx_status);
	vdev_id = __le32_to_cpu(ev->vdev_id);

	switch (tx_status) {
	case WMI_TLV_BCN_TX_STATUS_OK:
		break;
	case WMI_TLV_BCN_TX_STATUS_XRETRY:
	case WMI_TLV_BCN_TX_STATUS_DROP:
	case WMI_TLV_BCN_TX_STATUS_FILTERED:


		ath10k_warn(ar, "received bcn tmpl tx status on vdev %i: %d",
			    vdev_id, tx_status);
		break;
	}

	arvif = ath10k_get_arvif(ar, vdev_id);
	if (arvif && arvif->is_up && arvif->vif->csa_active)
		ieee80211_queue_work(ar->hw, &arvif->ap_csa_work);

	kfree(tb);
	return 0;
}
