xen_net_rate_changed(struct xenbus_watch *watch,
				const char **vec, unsigned int len)
{
	struct xenvif *vif = container_of(watch, struct xenvif, credit_watch);
	struct xenbus_device *dev = xenvif_to_xenbus_device(vif);
	unsigned long   credit_bytes;
	unsigned long   credit_usec;
	unsigned int queue_index;

	xen_net_read_rate(dev, &credit_bytes, &credit_usec);
	for (queue_index = 0; queue_index < vif->num_queues; queue_index++) {
		struct xenvif_queue *queue = &vif->queues[queue_index];

		queue->credit_bytes = credit_bytes;
		queue->credit_usec = credit_usec;
		if (!mod_timer_pending(&queue->credit_timeout, jiffies) &&
			queue->remaining_credit > queue->credit_bytes) {
			queue->remaining_credit = queue->credit_bytes;
		}
	}
}
