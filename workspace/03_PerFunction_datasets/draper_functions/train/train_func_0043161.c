rtl8187b_status_cb(struct urb *urb)
{
	struct ieee80211_hw *hw = (struct ieee80211_hw *)urb->context;
	struct rtl8187_priv *priv = hw->priv;
	u64 val;
	unsigned int cmd_type;

	if (unlikely(urb->status))
		return;


	val = le64_to_cpu(priv->b_tx_status.buf);

	cmd_type = (val >> 30) & 0x3;
	if (cmd_type == 1) {
		unsigned int pkt_rc, seq_no;
		bool tok;
		struct sk_buff *skb;
		struct ieee80211_hdr *ieee80211hdr;
		unsigned long flags;

		pkt_rc = val & 0xFF;
		tok = val & (1 << 15);
		seq_no = (val >> 16) & 0xFFF;

		spin_lock_irqsave(&priv->b_tx_status.queue.lock, flags);
		skb_queue_reverse_walk(&priv->b_tx_status.queue, skb) {
			ieee80211hdr = (struct ieee80211_hdr *)skb->data;


			if ((le16_to_cpu(ieee80211hdr->seq_ctrl)
			    & 0xFFF) == seq_no)
				break;
		}
		if (skb != (struct sk_buff *) &priv->b_tx_status.queue) {
			struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

			__skb_unlink(skb, &priv->b_tx_status.queue);
			if (tok)
				info->flags |= IEEE80211_TX_STAT_ACK;
			info->status.rates[0].count = pkt_rc + 1;

			ieee80211_tx_status_irqsafe(hw, skb);
		}
		spin_unlock_irqrestore(&priv->b_tx_status.queue.lock, flags);
	}

	usb_anchor_urb(urb, &priv->anchored);
	if (usb_submit_urb(urb, GFP_ATOMIC))
		usb_unanchor_urb(urb);
}
