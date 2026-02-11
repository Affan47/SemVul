rsi_program_bb_rf(struct rsi_common *common)
{
	struct sk_buff *skb;
	struct rsi_mac_frame *mgmt_frame;

	rsi_dbg(MGMT_TX_ZONE, "%s: Sending program BB/RF frame\n", __func__);

	skb = dev_alloc_skb(FRAME_DESC_SZ);
	if (!skb) {
		rsi_dbg(ERR_ZONE, "%s: Failed in allocation of skb\n",
			__func__);
		return -ENOMEM;
	}

	memset(skb->data, 0, FRAME_DESC_SZ);
	mgmt_frame = (struct rsi_mac_frame *)skb->data;

	mgmt_frame->desc_word[0] = cpu_to_le16(RSI_WIFI_MGMT_Q << 12);
	mgmt_frame->desc_word[1] = cpu_to_le16(BBP_PROG_IN_TA);
	mgmt_frame->desc_word[4] = cpu_to_le16(common->endpoint);

	if (common->rf_reset) {
		mgmt_frame->desc_word[7] =  cpu_to_le16(RF_RESET_ENABLE);
		rsi_dbg(MGMT_TX_ZONE, "%s: ===> RF RESET REQUEST SENT <===\n",
			__func__);
		common->rf_reset = 0;
	}
	common->bb_rf_prog_count = 1;
	mgmt_frame->desc_word[7] |= cpu_to_le16(PUT_BBP_RESET |
				     BBP_REG_WRITE | (RSI_RF_TYPE << 4));
	skb_put(skb, FRAME_DESC_SZ);

	return rsi_send_internal_mgmt_frame(common, skb);
}
