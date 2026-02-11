asd_free_queues(struct asd_ha_struct *asd_ha)
{
	unsigned long flags;
	LIST_HEAD(pending);
	struct list_head *n, *pos;

	spin_lock_irqsave(&asd_ha->seq.pend_q_lock, flags);
	asd_ha->seq.pending = 0;
	list_splice_init(&asd_ha->seq.pend_q, &pending);
	spin_unlock_irqrestore(&asd_ha->seq.pend_q_lock, flags);

	if (!list_empty(&pending))
		ASD_DPRINTK("Uh-oh! Pending is not empty!\n");

	list_for_each_safe(pos, n, &pending) {
		struct asd_ascb *ascb = list_entry(pos, struct asd_ascb, list);


		del_timer_sync(&ascb->timer);
		WARN_ON(ascb->scb->header.opcode != CONTROL_PHY);

		list_del_init(pos);
		ASD_DPRINTK("freeing from pending\n");
		asd_ascb_free(ascb);
	}
}
