_rtl92s_firmware_downloadcode(struct ieee80211_hw *hw,
		u8 *code_virtual_address, u32 buffer_len)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct sk_buff *skb;
	struct rtl_tcb_desc *tcb_desc;
	unsigned char *seg_ptr;
	u16 frag_threshold = MAX_FIRMWARE_CODE_SIZE;
	u16 frag_length, frag_offset = 0;
	u16 extra_descoffset = 0;
	u8 last_inipkt = 0;

	_rtl92s_fw_set_rqpn(hw);

	if (buffer_len >= MAX_FIRMWARE_CODE_SIZE) {
		RT_TRACE(rtlpriv, COMP_ERR, DBG_EMERG,
			 "Size over FIRMWARE_CODE_SIZE!\n");

		return false;
	}

	extra_descoffset = 0;

	do {
		if ((buffer_len - frag_offset) > frag_threshold) {
			frag_length = frag_threshold + extra_descoffset;
		} else {
			frag_length = (u16)(buffer_len - frag_offset +
					    extra_descoffset);
			last_inipkt = 1;
		}


		skb = dev_alloc_skb(frag_length);
		if (!skb)
			return false;
		skb_reserve(skb, extra_descoffset);
		seg_ptr = (u8 *)skb_put(skb, (u32)(frag_length -
					extra_descoffset));
		memcpy(seg_ptr, code_virtual_address + frag_offset,
		       (u32)(frag_length - extra_descoffset));

		tcb_desc = (struct rtl_tcb_desc *)(skb->cb);
		tcb_desc->queue_index = TXCMD_QUEUE;
		tcb_desc->cmd_or_init = DESC_PACKET_TYPE_INIT;
		tcb_desc->last_inipkt = last_inipkt;

		_rtl92s_cmd_send_packet(hw, skb, last_inipkt);

		frag_offset += (frag_length - extra_descoffset);

	} while (frag_offset < buffer_len);

	rtl_write_byte(rtlpriv, TP_POLL, TPPOLL_CQ);

	return true ;
}
