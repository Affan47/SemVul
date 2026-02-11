enable_timeout(TimeoutId id, TimestampTz now, TimestampTz fin_time)
{
	int			i;


	Assert(all_timeouts_initialized);
	Assert(all_timeouts[id].timeout_handler != NULL);


	i = find_active_timeout(id);
	if (i >= 0)
		remove_timeout_index(i);


	for (i = 0; i < num_active_timeouts; i++)
	{
		timeout_params *old_timeout = active_timeouts[i];

		if (fin_time < old_timeout->fin_time)
			break;
		if (fin_time == old_timeout->fin_time && id < old_timeout->index)
			break;
	}


	all_timeouts[id].indicator = false;
	all_timeouts[id].start_time = now;
	all_timeouts[id].fin_time = fin_time;

	insert_timeout(id, i);
}
