hip04_tx_reclaim(struct net_device *ndev, bool force)
{
	struct hip04_priv *priv = netdev_priv(ndev);
	unsigned tx_tail = priv->tx_tail;
	struct tx_desc *desc;
	unsigned int bytes_compl = 0, pkts_compl = 0;
	unsigned int count;

	smp_rmb();
	count = tx_count(ACCESS_ONCE(priv->tx_head), tx_tail);
	if (count == 0)
		goto out;

	while (count) {
		desc = &priv->tx_desc[tx_tail];
		if (desc->send_addr != 0) {
			if (force)
				desc->send_addr = 0;
			else
				break;
		}

		if (priv->tx_phys[tx_tail]) {
			dma_unmap_single(&ndev->dev, priv->tx_phys[tx_tail],
					 priv->tx_skb[tx_tail]->len,
					 DMA_TO_DEVICE);
			priv->tx_phys[tx_tail] = 0;
		}
		pkts_compl++;
		bytes_compl += priv->tx_skb[tx_tail]->len;
		dev_kfree_skb(priv->tx_skb[tx_tail]);
		priv->tx_skb[tx_tail] = NULL;
		tx_tail = TX_NEXT(tx_tail);
		count--;
	}

	priv->tx_tail = tx_tail;
	smp_wmb();

out:
	if (pkts_compl || bytes_compl)
		netdev_completed_queue(ndev, pkts_compl, bytes_compl);

	if (unlikely(netif_queue_stopped(ndev)) && (count < (TX_DESC_NUM - 1)))
		netif_wake_queue(ndev);

	return count;
}
