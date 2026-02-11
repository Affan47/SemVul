init_mad_queue(struct ib_mad_qp_info *qp_info,
			   struct ib_mad_queue *mad_queue)
{
	mad_queue->qp_info = qp_info;
	mad_queue->count = 0;
	spin_lock_init(&mad_queue->lock);
	INIT_LIST_HEAD(&mad_queue->list);
}
