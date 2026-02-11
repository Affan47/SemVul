ath10k_wmi_tlv_op_gen_wow_enable(struct ath10k *ar)
{
	struct wmi_tlv_wow_enable_cmd *cmd;
	struct wmi_tlv *tlv;
	struct sk_buff *skb;
	size_t len;

	len = sizeof(*tlv) + sizeof(*cmd);
	skb = ath10k_wmi_alloc_skb(ar, len);
	if (!skb)
		return ERR_PTR(-ENOMEM);

	tlv = (struct wmi_tlv *)skb->data;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_WOW_ENABLE_CMD);
	tlv->len = __cpu_to_le16(sizeof(*cmd));
	cmd = (void *)tlv->value;

	cmd->enable = __cpu_to_le32(1);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv wow enable\n");
	return skb;
}
