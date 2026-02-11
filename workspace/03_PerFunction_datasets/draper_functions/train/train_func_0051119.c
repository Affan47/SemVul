ipoib_cm_post_receive_nonsrq(struct net_device *dev,
					struct ipoib_cm_rx *rx,
					struct ib_recv_wr *wr,
					struct ib_sge *sge, int id)
{
	struct ipoib_dev_priv *priv = netdev_priv(dev);
	struct ib_recv_wr *bad_wr;
	int i, ret;

	wr->wr_id = id | IPOIB_OP_CM | IPOIB_OP_RECV;

	for (i = 0; i < IPOIB_CM_RX_SG; ++i)
		sge[i].addr = rx->rx_ring[id].mapping[i];

	ret = ib_post_recv(rx->qp, wr, &bad_wr);
	if (unlikely(ret)) {
		ipoib_warn(priv, "post recv failed for buf %d (%d)\n", id, ret);
		ipoib_cm_dma_unmap_rx(priv, IPOIB_CM_RX_SG - 1,
				      rx->rx_ring[id].mapping);
		dev_kfree_skb_any(rx->rx_ring[id].skb);
		rx->rx_ring[id].skb = NULL;
	}

	return ret;
}
