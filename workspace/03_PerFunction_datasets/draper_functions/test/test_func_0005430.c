event_run(void)
{
	unsigned int i;

	for (i = 0; i < MAX_EVENTS; i++)
	{
		if (event_table[i].active && (event_table[i].when <= CURRTIME))
		{

			last_event_ran = event_table[i].name;
			event_table[i].func(event_table[i].arg);
			event_time_min = -1;


			if (event_table[i].frequency)
				event_table[i].when = CURRTIME + event_table[i].frequency;
			else
			{

				last_event_ran = "<onceonly>";
				event_table[i].name = NULL;
				event_table[i].func = NULL;
				event_table[i].arg = NULL;
				event_table[i].active = false;

				claro_state.event--;
			}
		}
	}
}
