__connman_ippool_create(int index,
					unsigned int start,
					unsigned int range,
					ippool_collision_cb_t collision_cb,
					void *user_data)
{
	struct connman_ippool *pool;
	struct address_info *info;
	uint32_t block;

	DBG("");


	if (start + range > 254) {
		connman_error("IP pool does not support pool size larger than 254");
		return NULL;
	}

	block = get_free_block(start + range);
	if (block == 0) {
		connman_warn("Could not find a free IP block");
		return NULL;
	}

	pool = g_try_new0(struct connman_ippool, 1);
	if (pool == NULL)
		return NULL;

	info = g_try_new0(struct address_info, 1);
	if (info == NULL) {
		g_free(pool);
		return NULL;
	}

	last_block = block;

	info->index = index;
	info->start = block;
	info->end = block + range;

	pool->refcount = 1;
	pool->info = info;
	pool->collision_cb = collision_cb;
	pool->user_data = user_data;

	info->pool = pool;

	if (range == 0)
		range = 1;

	pool->gateway = get_ip(info->start + 1);
	pool->broadcast = get_ip(info->start + 255);
	pool->subnet_mask = get_ip(subnet_mask_24);
	pool->start_ip = get_ip(block + start);
	pool->end_ip = get_ip(block + start + range);

	allocated_blocks = g_slist_prepend(allocated_blocks, info);
	g_hash_table_insert(pool_hash, pool, pool);

	return pool;
}
