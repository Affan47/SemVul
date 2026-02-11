vmw_marker_pull(struct vmw_marker_queue *queue,
		   uint32_t signaled_seqno)
{
	struct vmw_marker *marker, *next;
	bool updated = false;
	u64 now;

	spin_lock(&queue->lock);
	now = ktime_get_raw_ns();

	if (list_empty(&queue->head)) {
		queue->lag = 0;
		queue->lag_time = now;
		updated = true;
		goto out_unlock;
	}

	list_for_each_entry_safe(marker, next, &queue->head, head) {
		if (signaled_seqno - marker->seqno > (1 << 30))
			continue;

		queue->lag = now - marker->submitted;
		queue->lag_time = now;
		updated = true;
		list_del(&marker->head);
		kfree(marker);
	}

out_unlock:
	spin_unlock(&queue->lock);

	return (updated) ? 0 : -EBUSY;
}
