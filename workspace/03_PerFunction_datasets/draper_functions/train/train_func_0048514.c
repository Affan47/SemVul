il4965_tx_queue_reclaim(struct il_priv *il, int txq_id, int idx)
{
	struct il_tx_queue *txq = &il->txq[txq_id];
	struct il_queue *q = &txq->q;
	int nfreed = 0;
	struct ieee80211_hdr *hdr;
	struct sk_buff *skb;

	if (idx >= q->n_bd || il_queue_used(q, idx) == 0) {
		IL_ERR("Read idx for DMA queue txq id (%d), idx %d, "
		       "is out of range [0-%d] %d %d.\n", txq_id, idx, q->n_bd,
		       q->write_ptr, q->read_ptr);
		return 0;
	}

	for (idx = il_queue_inc_wrap(idx, q->n_bd); q->read_ptr != idx;
	     q->read_ptr = il_queue_inc_wrap(q->read_ptr, q->n_bd)) {

		skb = txq->skbs[txq->q.read_ptr];

		if (WARN_ON_ONCE(skb == NULL))
			continue;

		hdr = (struct ieee80211_hdr *) skb->data;
		if (ieee80211_is_data_qos(hdr->frame_control))
			nfreed++;

		il4965_tx_status(il, skb, txq_id >= IL4965_FIRST_AMPDU_QUEUE);

		txq->skbs[txq->q.read_ptr] = NULL;
		il->ops->txq_free_tfd(il, txq);
	}
	return nfreed;
}
