dvb_dmxdev_set_buffer_size(struct dmxdev_filter *dmxdevfilter,
				      unsigned long size)
{
	struct dvb_ringbuffer *buf = &dmxdevfilter->buffer;
	void *newmem;
	void *oldmem;

	if (buf->size == size)
		return 0;
	if (!size)
		return -EINVAL;
	if (dmxdevfilter->state >= DMXDEV_STATE_GO)
		return -EBUSY;

	newmem = vmalloc(size);
	if (!newmem)
		return -ENOMEM;

	oldmem = buf->data;

	spin_lock_irq(&dmxdevfilter->dev->lock);
	buf->data = newmem;
	buf->size = size;


	dvb_ringbuffer_reset(buf);
	spin_unlock_irq(&dmxdevfilter->dev->lock);

	vfree(oldmem);

	return 0;
}
