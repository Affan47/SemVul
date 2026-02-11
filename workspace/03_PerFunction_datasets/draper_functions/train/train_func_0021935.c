dwceqos_start_xmit(struct sk_buff *skb, struct net_device *ndev)
{
	struct net_local *lp = netdev_priv(ndev);
	struct dwceqos_tx trans;
	int err;

	dwceqos_tx_prepare(skb, lp, &trans);
	if (lp->tx_free < trans.nr_descriptors) {
		netif_stop_queue(ndev);
		return NETDEV_TX_BUSY;
	}

	err = dwceqos_tx_linear(skb, lp, &trans);
	if (err)
		goto tx_error;

	err = dwceqos_tx_frags(skb, lp, &trans);
	if (err)
		goto tx_error;

	WARN_ON(lp->tx_next !=
		((trans.initial_descriptor + trans.nr_descriptors) %
		 DWCEQOS_TX_DCNT));

	dwceqos_tx_finalize(skb, lp, &trans);

	netdev_sent_queue(ndev, skb->len);

	spin_lock_bh(&lp->tx_lock);
	lp->tx_free -= trans.nr_descriptors;
	spin_unlock_bh(&lp->tx_lock);

	ndev->trans_start = jiffies;
	return 0;

tx_error:
	dwceqos_tx_rollback(lp, &trans);
	dev_kfree_skb(skb);
	return 0;
}
