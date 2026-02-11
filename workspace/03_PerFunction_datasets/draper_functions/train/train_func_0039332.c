ack_quiescing(struct cache *cache)
{
	if (is_quiescing(cache)) {
		atomic_inc(&cache->quiescing_ack);
		wake_up(&cache->quiescing_wait);
	}
}
