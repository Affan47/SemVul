mono_hazard_pointer_save_for_signal_handler (void)
{
	int small_id, i;
	MonoThreadHazardPointers *hp = mono_hazard_pointer_get ();
	MonoThreadHazardPointers *hp_overflow;

	for (i = 0; i < HAZARD_POINTER_COUNT; ++i)
		if (hp->hazard_pointers [i])
			goto search;
	return -1;

 search:
	for (small_id = 0; small_id < HAZARD_TABLE_OVERFLOW; ++small_id) {
		if (!overflow_busy [small_id])
			break;
	}


	g_assert (small_id < HAZARD_TABLE_OVERFLOW);

	if (InterlockedCompareExchange (&overflow_busy [small_id], 1, 0) != 0)
		goto search;

	hp_overflow = &hazard_table [small_id];

	for (i = 0; i < HAZARD_POINTER_COUNT; ++i)
		g_assert (!hp_overflow->hazard_pointers [i]);
	*hp_overflow = *hp;

	mono_memory_write_barrier ();

	memset (hp, 0, sizeof (MonoThreadHazardPointers));

	return small_id;
}
