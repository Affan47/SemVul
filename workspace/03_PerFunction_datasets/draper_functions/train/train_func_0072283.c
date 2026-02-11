rt2x00queue_uninitialize(struct rt2x00_dev *rt2x00dev)
{
	struct data_queue *queue;

	rt2x00queue_free_skbs(rt2x00dev->rx);

	queue_for_each(rt2x00dev, queue) {
		kfree(queue->entries);
		queue->entries = NULL;
	}
}
