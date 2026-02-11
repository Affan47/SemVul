saa7134_vbi_init1(struct saa7134_dev *dev)
{
	INIT_LIST_HEAD(&dev->vbi_q.queue);
	init_timer(&dev->vbi_q.timeout);
	dev->vbi_q.timeout.function = saa7134_buffer_timeout;
	dev->vbi_q.timeout.data     = (unsigned long)(&dev->vbi_q);
	dev->vbi_q.dev              = dev;

	if (vbibufs < 2)
		vbibufs = 2;
	if (vbibufs > VIDEO_MAX_FRAME)
		vbibufs = VIDEO_MAX_FRAME;
	return 0;
}
