queue_wake_up_all(struct genwqe_dev *cd)
{
	unsigned int i;
	unsigned long flags;
	struct ddcb_queue *queue = &cd->queue;

	spin_lock_irqsave(&queue->ddcb_lock, flags);

	for (i = 0; i < queue->ddcb_max; i++)
		wake_up_interruptible(&queue->ddcb_waitqs[queue->ddcb_act]);

	wake_up_interruptible(&queue->busy_waitq);
	spin_unlock_irqrestore(&queue->ddcb_lock, flags);

	return 0;
}
