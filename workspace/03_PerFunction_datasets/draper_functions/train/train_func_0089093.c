ssd_init_tag(struct ssd_device *dev)
{
	int nr_ulongs = ALIGN(dev->hw_info.cmd_fifo_sz, BITS_PER_LONG) / BITS_PER_LONG;

	mutex_init(&dev->barrier_mutex);

	atomic_set(&dev->queue_depth, dev->hw_info.cmd_fifo_sz);

	dev->tag_map = kmalloc(nr_ulongs * sizeof(unsigned long), GFP_ATOMIC);
	if (!dev->tag_map) {
		return -ENOMEM;
	}

	memset(dev->tag_map, 0, nr_ulongs * sizeof(unsigned long));

	init_waitqueue_head(&dev->tag_wq);

	return 0;
}
