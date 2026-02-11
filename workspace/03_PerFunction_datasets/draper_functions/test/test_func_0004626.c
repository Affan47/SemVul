free_buffer(struct videobuf_queue *vq, struct tm6000_buffer *buf)
{
	struct tm6000_fh *fh = vq->priv_data;
	struct tm6000_core   *dev = fh->dev;
	unsigned long flags;

	BUG_ON(in_interrupt());


	spin_lock_irqsave(&dev->slock, flags);
	if (dev->isoc_ctl.buf == buf)
		dev->isoc_ctl.buf = NULL;
	spin_unlock_irqrestore(&dev->slock, flags);

	videobuf_vmalloc_free(&buf->vb);
	buf->vb.state = VIDEOBUF_NEEDS_INIT;
}
