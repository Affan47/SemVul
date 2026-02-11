backoff_new(int timer_type, int initial_interval, int max_interval)
{
	Backoff_Timer *bt;

	bt = (Backoff_Timer *)slapi_ch_calloc(1, sizeof(struct backoff_timer));
	bt->type = timer_type;
	bt->initial_interval = initial_interval;
	bt->next_interval = bt->initial_interval;
	bt->max_interval = max_interval;
	bt->running = 0;
	if ((bt->lock = PR_NewLock()) == NULL)
	{
		slapi_ch_free((void **)&bt);
	}
	return bt;
}
