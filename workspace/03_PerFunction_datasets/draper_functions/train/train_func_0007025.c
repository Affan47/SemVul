__get_txreq(struct hfi1_ibdev *dev,
						struct hfi1_qp *qp)
{
	struct verbs_txreq *tx;
	unsigned long flags;

	tx = kmem_cache_alloc(dev->verbs_txreq_cache, GFP_ATOMIC);
	if (!tx) {
		spin_lock_irqsave(&qp->s_lock, flags);
		write_seqlock(&dev->iowait_lock);
		if (ib_hfi1_state_ops[qp->state] & HFI1_PROCESS_RECV_OK &&
		    list_empty(&qp->s_iowait.list)) {
			dev->n_txwait++;
			qp->s_flags |= HFI1_S_WAIT_TX;
			list_add_tail(&qp->s_iowait.list, &dev->txwait);
			trace_hfi1_qpsleep(qp, HFI1_S_WAIT_TX);
			atomic_inc(&qp->refcount);
		}
		qp->s_flags &= ~HFI1_S_BUSY;
		write_sequnlock(&dev->iowait_lock);
		spin_unlock_irqrestore(&qp->s_lock, flags);
		tx = ERR_PTR(-EBUSY);
	}
	return tx;
}
