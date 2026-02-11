get_txreq(struct ipath_ibdev *dev)
{
	struct ipath_verbs_txreq *tx = NULL;
	unsigned long flags;

	spin_lock_irqsave(&dev->pending_lock, flags);
	if (!list_empty(&dev->txreq_free)) {
		struct list_head *l = dev->txreq_free.next;

		list_del(l);
		tx = list_entry(l, struct ipath_verbs_txreq, txreq.list);
	}
	spin_unlock_irqrestore(&dev->pending_lock, flags);
	return tx;
}
