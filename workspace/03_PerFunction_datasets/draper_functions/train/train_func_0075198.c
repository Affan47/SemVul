memcg_alloc_cache_id(void)
{
	int id, size;
	int err;

	id = ida_simple_get(&memcg_cache_ida,
			    0, MEMCG_CACHES_MAX_SIZE, GFP_KERNEL);
	if (id < 0)
		return id;

	if (id < memcg_nr_cache_ids)
		return id;


	down_write(&memcg_cache_ids_sem);

	size = 2 * (id + 1);
	if (size < MEMCG_CACHES_MIN_SIZE)
		size = MEMCG_CACHES_MIN_SIZE;
	else if (size > MEMCG_CACHES_MAX_SIZE)
		size = MEMCG_CACHES_MAX_SIZE;

	err = memcg_update_all_caches(size);
	if (!err)
		err = memcg_update_all_list_lrus(size);
	if (!err)
		memcg_nr_cache_ids = size;

	up_write(&memcg_cache_ids_sem);

	if (err) {
		ida_simple_remove(&memcg_cache_ida, id);
		return err;
	}
	return id;
}
