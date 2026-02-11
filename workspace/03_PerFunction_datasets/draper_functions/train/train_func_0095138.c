rt2x00queue_start_queue(struct data_queue *queue)
{
	mutex_lock(&queue->status_lock);

	if (!test_bit(DEVICE_STATE_PRESENT, &queue->rt2x00dev->flags) ||
	    test_and_set_bit(QUEUE_STARTED, &queue->flags)) {
		mutex_unlock(&queue->status_lock);
		return;
	}

	set_bit(QUEUE_PAUSED, &queue->flags);

	queue->rt2x00dev->ops->lib->start_queue(queue);

	rt2x00queue_unpause_queue(queue);

	mutex_unlock(&queue->status_lock);
}
