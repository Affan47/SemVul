enablepool(struct io_data *io_data, __maybe_unused SOCKETTYPE c, char *param, bool isjson, __maybe_unused char group)
{
	struct pool *pool;
	int id;

	if (total_pools == 0) {
		message(io_data, MSG_NOPOOL, 0, NULL, isjson);
		return;
	}

	if (param == NULL || *param == '\0') {
		message(io_data, MSG_MISPID, 0, NULL, isjson);
		return;
	}

	id = atoi(param);
	if (id < 0 || id >= total_pools) {
		message(io_data, MSG_INVPID, id, NULL, isjson);
		return;
	}

	pool = pools[id];
	if (pool->enabled == POOL_ENABLED) {
		message(io_data, MSG_ALRENAP, id, NULL, isjson);
		return;
	}

	pool->enabled = POOL_ENABLED;
	if (pool->prio < current_pool()->prio)
		switch_pools(pool);

	message(io_data, MSG_ENAPOOL, id, NULL, isjson);
}
