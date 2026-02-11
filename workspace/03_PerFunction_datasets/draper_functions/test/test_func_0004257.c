work_decode(struct pool *pool, struct work *work, json_t *val)
{
	json_t *res_val = json_object_get(val, "result");
	bool ret = false;

	cgtime(&pool->tv_lastwork);
	if (!res_val || json_is_null(res_val)) {
		applog(LOG_ERR, "JSON Failed to decode result");
		goto out;
	}

	if (pool->has_gbt) {
		if (unlikely(!gbt_decode(pool, res_val)))
			goto out;
		work->gbt = true;
		ret = true;
		goto out;
	} else if (unlikely(!getwork_decode(res_val, work)))
		goto out;

	memset(work->hash, 0, sizeof(work->hash));

	cgtime(&work->tv_staged);

	ret = true;

out:
	return ret;
}
