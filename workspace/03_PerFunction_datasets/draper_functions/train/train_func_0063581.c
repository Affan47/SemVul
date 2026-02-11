cache_expire_unused (Cache *cache)
{
	ListNode *node, *prev;

	node = cache->list.tailpred;
	while (node->prev && cache->size > cache->max_size) {
		prev = node->prev;
		if (cache->expire (cache, (CacheNode *) node)) {
			list_unlink (node);
			g_hash_table_remove (cache->node_hash, ((CacheNode *) node)->key);
			cache->size--;
		}
		node = prev;
	}
}
