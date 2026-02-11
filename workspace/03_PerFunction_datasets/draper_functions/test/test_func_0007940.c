ar5523_data_tx_cb(struct urb *urb)
{
	struct sk_buff *skb = urb->context;
	struct ieee80211_tx_info *txi = IEEE80211_SKB_CB(skb);
	struct ar5523_tx_data *data = (struct ar5523_tx_data *)
				       txi->driver_data;
	struct ar5523 *ar = data->ar;
	unsigned long flags;

	ar5523_dbg(ar, "data tx urb completed: %d\n", urb->status);

	spin_lock_irqsave(&ar->tx_data_list_lock, flags);
	list_del(&data->list);
	spin_unlock_irqrestore(&ar->tx_data_list_lock, flags);

	if (urb->status) {
		ar5523_dbg(ar, "%s: urb status: %d\n", __func__, urb->status);
		ar5523_data_tx_pkt_put(ar);
		ieee80211_free_txskb(ar->hw, skb);
	} else {
		skb_pull(skb, sizeof(struct ar5523_tx_desc) + sizeof(__be32));
		ieee80211_tx_status_irqsafe(ar->hw, skb);
	}
	usb_free_urb(urb);
}
