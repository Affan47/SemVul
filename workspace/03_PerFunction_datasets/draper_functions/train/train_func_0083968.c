rrl_reseed(rrl_table_t *rrl)
{

	if (rrl->lk_count > 0) {
		pthread_mutex_lock(&rrl->ll);
		for (unsigned i = 0; i < rrl->lk_count; ++i) {
			rrl_lock(rrl, i);
		}
	}

	memset(rrl->arr, 0, rrl->size * sizeof(rrl_item_t));
	rrl->seed = knot_random_uint32_t();
	dbg_rrl("%s: reseed to '%u'\n", __func__, rrl->seed);

	if (rrl->lk_count > 0) {
		for (unsigned i = 0; i < rrl->lk_count; ++i) {
			rrl_unlock(rrl, i);
		}
		pthread_mutex_unlock(&rrl->ll);
	}

	return KNOT_EOK;
}
