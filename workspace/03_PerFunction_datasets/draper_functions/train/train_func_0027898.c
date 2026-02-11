ipw_net_is_queue_full(struct net_device *dev, int pri)
{
	struct ipw_priv *priv = libipw_priv(dev);
#ifdef CONFIG_IPW2200_QOS
	int tx_id = ipw_get_tx_queue_number(priv, pri);
	struct clx2_tx_queue *txq = &priv->txq[tx_id];
#else
	struct clx2_tx_queue *txq = &priv->txq[0];
#endif

	if (ipw_tx_queue_space(&txq->q) < txq->q.high_mark)
		return 1;

	return 0;
}
