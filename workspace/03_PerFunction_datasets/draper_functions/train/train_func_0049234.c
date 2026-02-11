saa7134_buffer_queue(struct saa7134_dev *dev,
			 struct saa7134_dmaqueue *q,
			 struct saa7134_buf *buf)
{
	struct saa7134_buf *next = NULL;
	unsigned long flags;

	spin_lock_irqsave(&dev->slock, flags);
	core_dbg("buffer_queue %p\n", buf);
	if (NULL == q->curr) {
		if (!q->need_two) {
			q->curr = buf;
			buf->activate(dev, buf, NULL);
		} else if (list_empty(&q->queue)) {
			list_add_tail(&buf->entry, &q->queue);
		} else {
			next = list_entry(q->queue.next, struct saa7134_buf,
					  entry);
			q->curr = buf;
			buf->activate(dev, buf, next);
		}
	} else {
		list_add_tail(&buf->entry, &q->queue);
	}
	spin_unlock_irqrestore(&dev->slock, flags);
	return 0;
}
