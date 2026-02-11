niu_tx_work(struct niu *np, struct tx_ring_info *rp)
{
	struct netdev_queue *txq;
	u16 pkt_cnt, tmp;
	int cons, index;
	u64 cs;

	index = (rp - np->tx_rings);
	txq = netdev_get_tx_queue(np->dev, index);

	cs = rp->tx_cs;
	if (unlikely(!(cs & (TX_CS_MK | TX_CS_MMK))))
		goto out;

	tmp = pkt_cnt = (cs & TX_CS_PKT_CNT) >> TX_CS_PKT_CNT_SHIFT;
	pkt_cnt = (pkt_cnt - rp->last_pkt_cnt) &
		(TX_CS_PKT_CNT >> TX_CS_PKT_CNT_SHIFT);

	rp->last_pkt_cnt = tmp;

	cons = rp->cons;

	netif_printk(np, tx_done, KERN_DEBUG, np->dev,
		     "%s() pkt_cnt[%u] cons[%d]\n", __func__, pkt_cnt, cons);

	while (pkt_cnt--)
		cons = release_tx_packet(np, rp, cons);

	rp->cons = cons;
	smp_mb();

out:
	if (unlikely(netif_tx_queue_stopped(txq) &&
		     (niu_tx_avail(rp) > NIU_TX_WAKEUP_THRESH(rp)))) {
		__netif_tx_lock(txq, smp_processor_id());
		if (netif_tx_queue_stopped(txq) &&
		    (niu_tx_avail(rp) > NIU_TX_WAKEUP_THRESH(rp)))
			netif_tx_wake_queue(txq);
		__netif_tx_unlock(txq);
	}
}
