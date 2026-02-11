cw1200_queue_get_num_queued(struct cw1200_queue *queue,
				   u32 link_id_map)
{
	size_t ret;
	int i, bit;
	size_t map_capacity = queue->stats->map_capacity;

	if (!link_id_map)
		return 0;

	spin_lock_bh(&queue->lock);
	if (link_id_map == (u32)-1) {
		ret = queue->num_queued - queue->num_pending;
	} else {
		ret = 0;
		for (i = 0, bit = 1; i < map_capacity; ++i, bit <<= 1) {
			if (link_id_map & bit)
				ret += queue->link_map_cache[i];
		}
	}
	spin_unlock_bh(&queue->lock);
	return ret;
}
