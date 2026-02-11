rt2x00queue_free_skbs(struct data_queue *queue)
{
	unsigned int i;

	if (!queue->entries)
		return;

	for (i = 0; i < queue->limit; i++) {
		rt2x00queue_free_skb(&queue->entries[i]);
	}
}
