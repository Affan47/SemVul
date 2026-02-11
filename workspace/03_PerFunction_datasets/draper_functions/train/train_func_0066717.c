rt2800mmio_enable_radio(struct rt2x00_dev *rt2x00dev)
{

	rt2800_wait_wpdma_ready(rt2x00dev);

	if (unlikely(rt2800mmio_init_queues(rt2x00dev)))
		return -EIO;

	return rt2800_enable_radio(rt2x00dev);
}
