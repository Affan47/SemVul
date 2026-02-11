cx23885_wakeup(struct cx23885_tsport *port,
			   struct cx23885_dmaqueue *q, u32 count)
{
	struct cx23885_dev *dev = port->dev;
	struct cx23885_buffer *buf;

	if (list_empty(&q->active))
		return;
	buf = list_entry(q->active.next,
			 struct cx23885_buffer, queue);

	v4l2_get_timestamp(&buf->vb.timestamp);
	buf->vb.sequence = q->count++;
	dprintk(1, "[%p/%d] wakeup reg=%d buf=%d\n", buf,
		buf->vb.vb2_buf.index,
		count, q->count);
	list_del(&buf->queue);
	vb2_buffer_done(&buf->vb.vb2_buf, VB2_BUF_STATE_DONE);
}
