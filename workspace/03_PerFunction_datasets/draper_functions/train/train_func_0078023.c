workers_steal (WorkerData *data, WorkerData *victim_data, gboolean lock)
{
	SgenGrayQueue *queue = &data->private_gray_queue;
	int num, n;

	g_assert (!queue->first);

	if (!victim_data->stealable_stack_fill)
		return FALSE;

	if (lock && mono_mutex_trylock (&victim_data->stealable_stack_mutex))
		return FALSE;

	n = num = (victim_data->stealable_stack_fill + 1) / 2;


	while (n > 0) {
		int m = MIN (SGEN_GRAY_QUEUE_SECTION_SIZE, n);
		n -= m;

		sgen_gray_object_alloc_queue_section (queue);
		memcpy (queue->first->objects,
				victim_data->stealable_stack + victim_data->stealable_stack_fill - num + n,
				sizeof (char*) * m);
		queue->first->end = m;
	}

	victim_data->stealable_stack_fill -= num;

	if (lock)
		mono_mutex_unlock (&victim_data->stealable_stack_mutex);

	if (data == victim_data) {
		if (lock)
			stat_workers_stolen_from_self_lock += num;
		else
			stat_workers_stolen_from_self_no_lock += num;
	} else {
		stat_workers_stolen_from_others += num;
	}

	return num != 0;
}
