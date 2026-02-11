go_data_cache_finalize (GObject *obj)
{
	GODataCache *cache = (GODataCache *)obj;
	unsigned int i, j;

	if (NULL != cache->records) {
		GODataCacheField const *f;
		gpointer p;

		for (i = cache->fields->len ; i-- > 0 ; ) {
			f = g_ptr_array_index (cache->fields, i);
			if (GO_DATA_CACHE_FIELD_TYPE_INLINE == f->ref_type) {
				for (j = cache->records_len ; j-- > 0 ; ) {
					p = go_data_cache_records_index (cache, j) + f->offset;
					go_val_free (*((GOVal **)p));
				}
			}
		}
		g_free (cache->records);
		cache->records = NULL;
		cache->records_len = cache->records_allocated = 0;
	}

	for (i = cache->fields->len ; i-- > 0 ; )
		g_object_unref (g_ptr_array_index (cache->fields, i));
	g_ptr_array_free (cache->fields, TRUE);
	cache->fields = NULL;

	if (NULL != cache->data_source) {
		g_object_unref (cache->data_source);
		cache->data_source = NULL;
	}

	g_free (cache->refreshed_by);
	go_val_free (cache->refreshed_on);

	(parent_klass->finalize) (obj);
}
