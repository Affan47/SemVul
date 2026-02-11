backoff_reset(Backoff_Timer *bt, slapi_eq_fn_t callback, void *callback_data)
{
	time_t return_value = 0UL;

	PR_ASSERT(NULL != bt);
	PR_ASSERT(NULL != callback);

	PR_Lock(bt->lock);
	bt->running = 1;
	bt->callback = callback;
	bt->callback_arg = callback_data;

	if (NULL != bt->pending_event)
	{
		slapi_eq_cancel(bt->pending_event);
		bt->pending_event = NULL;
	}

	if (BACKOFF_RANDOM == bt->type)
	{
		bt->next_interval = random_interval_in_range(bt->initial_interval,
			bt->max_interval);
	}
	else
	{
		bt->next_interval = bt->initial_interval;
	}

	time(&bt->last_fire_time);
	return_value = bt->last_fire_time + bt->next_interval;
	bt->pending_event = slapi_eq_once(bt->callback, bt->callback_arg,
		return_value);
	PR_Unlock(bt->lock);
	return return_value;
}
