queue_poll_store(struct request_queue *q, const char *page,
				size_t count)
{
	unsigned long poll_on;
	ssize_t ret;

	if (!q->mq_ops || !q->mq_ops->poll)
		return -EINVAL;

	ret = queue_var_store(&poll_on, page, count);
	if (ret < 0)
		return ret;

	spin_lock_irq(q->queue_lock);
	if (poll_on)
		queue_flag_set(QUEUE_FLAG_POLL, q);
	else
		queue_flag_clear(QUEUE_FLAG_POLL, q);
	spin_unlock_irq(q->queue_lock);

	return ret;
}
