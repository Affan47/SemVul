pspoll_send_buffered(local_info_t *local, struct sta_info *sta,
				 struct sk_buff *skb)
{
	struct hostap_skb_tx_data *meta;

	if (!(sta->flags & WLAN_STA_PS)) {


		dev_queue_xmit(skb);
		return;
	}


	meta = (struct hostap_skb_tx_data *) skb->cb;
	meta->flags |= HOSTAP_TX_FLAGS_BUFFERED_FRAME;
	if (!skb_queue_empty(&sta->tx_buf)) {

		meta->flags |= HOSTAP_TX_FLAGS_ADD_MOREDATA;
	}
	dev_queue_xmit(skb);
}
