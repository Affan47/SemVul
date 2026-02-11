saa7146_buffer_timeout(unsigned long data)
{
	struct saa7146_dmaqueue *q = (struct saa7146_dmaqueue*)data;
	struct saa7146_dev *dev = q->dev;
	unsigned long flags;

	DEB_EE("dev:%p, dmaq:%p\n", dev, q);

	spin_lock_irqsave(&dev->slock,flags);
	if (q->curr) {
		DEB_D("timeout on %p\n", q->curr);
		saa7146_buffer_finish(dev,q,VIDEOBUF_ERROR);
	}


	spin_unlock_irqrestore(&dev->slock,flags);
}
