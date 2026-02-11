bcsp_dequeue(struct hci_uart *hu)
{
	struct bcsp_struct *bcsp = hu->priv;
	unsigned long flags;
	struct sk_buff *skb;


	skb = skb_dequeue(&bcsp->unrel);
	if (skb != NULL) {
		struct sk_buff *nskb = bcsp_prepare_pkt(bcsp, skb->data, skb->len, bt_cb(skb)->pkt_type);
		if (nskb) {
			kfree_skb(skb);
			return nskb;
		} else {
			skb_queue_head(&bcsp->unrel, skb);
			BT_ERR("Could not dequeue pkt because alloc_skb failed");
		}
	}


	spin_lock_irqsave_nested(&bcsp->unack.lock, flags, SINGLE_DEPTH_NESTING);

	if (bcsp->unack.qlen < BCSP_TXWINSIZE) {
		skb = skb_dequeue(&bcsp->rel);
		if (skb != NULL) {
			struct sk_buff *nskb = bcsp_prepare_pkt(bcsp, skb->data, skb->len,
								bt_cb(skb)->pkt_type);
			if (nskb) {
				__skb_queue_tail(&bcsp->unack, skb);
				mod_timer(&bcsp->tbcsp, jiffies + HZ / 4);
				spin_unlock_irqrestore(&bcsp->unack.lock, flags);
				return nskb;
			} else {
				skb_queue_head(&bcsp->rel, skb);
				BT_ERR("Could not dequeue pkt because alloc_skb failed");
			}
		}
	}

	spin_unlock_irqrestore(&bcsp->unack.lock, flags);


	if (bcsp->txack_req) {


		struct sk_buff *nskb = bcsp_prepare_pkt(bcsp, NULL, 0, BCSP_ACK_PKT);
		return nskb;
	}


	return NULL;
}
