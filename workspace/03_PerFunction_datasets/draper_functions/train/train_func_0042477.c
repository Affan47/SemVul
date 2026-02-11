ips_removeq_scb(ips_scb_queue_t * queue, ips_scb_t * item)
{
	ips_scb_t *p;

	METHOD_TRACE("ips_removeq_scb", 1);

	if (!item)
		return (NULL);

	if (item == queue->head) {
		return (ips_removeq_scb_head(queue));
	}

	p = queue->head;

	while ((p) && (item != p->q_next))
		p = p->q_next;

	if (p) {

		p->q_next = item->q_next;

		if (!item->q_next)
			queue->tail = p;

		item->q_next = NULL;
		queue->count--;

		return (item);
	}

	return (NULL);
}
