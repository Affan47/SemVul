make_room_for_new_entry (SoupCache *cache, guint length_to_add)
{
	GList *lru_entry = cache->priv->lru_start;


	while (lru_entry &&
	       (length_to_add + cache->priv->size > cache->priv->max_size)) {
		SoupCacheEntry *old_entry = (SoupCacheEntry *)lru_entry->data;


		if (soup_cache_entry_remove (cache, old_entry, TRUE))
			lru_entry = cache->priv->lru_start;
		else
			lru_entry = g_list_next (lru_entry);
	}
}
