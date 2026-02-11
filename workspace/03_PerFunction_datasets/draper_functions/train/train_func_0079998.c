ipoib_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct ipoib_dev_priv *priv = netdev_priv(dev);
	struct ipoib_neigh *neigh;
	struct ipoib_pseudo_header *phdr;
	struct ipoib_header *header;
	unsigned long flags;

	phdr = (struct ipoib_pseudo_header *) skb->data;
	skb_pull(skb, sizeof(*phdr));
	header = (struct ipoib_header *) skb->data;

	if (unlikely(phdr->hwaddr[4] == 0xff)) {

		if ((header->proto != htons(ETH_P_IP)) &&
		    (header->proto != htons(ETH_P_IPV6)) &&
		    (header->proto != htons(ETH_P_ARP)) &&
		    (header->proto != htons(ETH_P_RARP)) &&
		    (header->proto != htons(ETH_P_TIPC))) {

			++dev->stats.tx_dropped;
			dev_kfree_skb_any(skb);
			return NETDEV_TX_OK;
		}

		phdr->hwaddr[8] = (priv->pkey >> 8) & 0xff;
		phdr->hwaddr[9] = priv->pkey & 0xff;

		neigh = ipoib_neigh_get(dev, phdr->hwaddr);
		if (likely(neigh))
			goto send_using_neigh;
		ipoib_mcast_send(dev, phdr->hwaddr, skb);
		return NETDEV_TX_OK;
	}


	switch (header->proto) {
	case htons(ETH_P_IP):
	case htons(ETH_P_IPV6):
	case htons(ETH_P_TIPC):
		neigh = ipoib_neigh_get(dev, phdr->hwaddr);
		if (unlikely(!neigh)) {
			neigh_add_path(skb, phdr->hwaddr, dev);
			return NETDEV_TX_OK;
		}
		break;
	case htons(ETH_P_ARP):
	case htons(ETH_P_RARP):

		unicast_arp_send(skb, dev, phdr);
		return NETDEV_TX_OK;
	default:

		++dev->stats.tx_dropped;
		dev_kfree_skb_any(skb);
		return NETDEV_TX_OK;
	}

send_using_neigh:

	if (ipoib_cm_get(neigh)) {
		if (ipoib_cm_up(neigh)) {
			ipoib_cm_send(dev, skb, ipoib_cm_get(neigh));
			goto unref;
		}
	} else if (neigh->ah) {
		ipoib_send(dev, skb, neigh->ah, IPOIB_QPN(phdr->hwaddr));
		goto unref;
	}

	if (skb_queue_len(&neigh->queue) < IPOIB_MAX_PATH_REC_QUEUE) {
		push_pseudo_header(skb, phdr->hwaddr);
		spin_lock_irqsave(&priv->lock, flags);
		__skb_queue_tail(&neigh->queue, skb);
		spin_unlock_irqrestore(&priv->lock, flags);
	} else {
		++dev->stats.tx_dropped;
		dev_kfree_skb_any(skb);
	}

unref:
	ipoib_neigh_put(neigh);

	return NETDEV_TX_OK;
}
