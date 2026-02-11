_rtl_update_earlymode_info(struct ieee80211_hw *hw,
		struct sk_buff *skb, struct rtl_tcb_desc *tcb_desc, u8 tid)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct sk_buff *next_skb;
	u8 additionlen = FCS_LEN;


	if (info->control.hw_key)
		additionlen += info->control.hw_key->icv_len;


	tcb_desc->empkt_num = 0;
	spin_lock_bh(&rtlpriv->locks.waitq_lock);
	skb_queue_walk(&rtlpriv->mac80211.skb_waitq[tid], next_skb) {
		struct ieee80211_tx_info *next_info;

		next_info = IEEE80211_SKB_CB(next_skb);
		if (next_info->flags & IEEE80211_TX_CTL_AMPDU) {
			tcb_desc->empkt_len[tcb_desc->empkt_num] =
				next_skb->len + additionlen;
			tcb_desc->empkt_num++;
		} else {
			break;
		}

		if (skb_queue_is_last(&rtlpriv->mac80211.skb_waitq[tid],
				      next_skb))
			break;

		if (tcb_desc->empkt_num >= rtlhal->max_earlymode_num)
			break;
	}
	spin_unlock_bh(&rtlpriv->locks.waitq_lock);

	return true;
}
