dcookie_exit(void)
{
	struct list_head * list;
	struct list_head * pos;
	struct list_head * pos2;
	struct dcookie_struct * dcs;
	size_t i;

	for (i = 0; i < hash_size; ++i) {
		list = dcookie_hashtable + i;
		list_for_each_safe(pos, pos2, list) {
			dcs = list_entry(pos, struct dcookie_struct, hash_list);
			list_del(&dcs->hash_list);
			free_dcookie(dcs);
		}
	}

	kfree(dcookie_hashtable);
	kmem_cache_destroy(dcookie_cache);
}
