check_high_alarm_limit(GkrellmAlert *alert, gfloat value)
	{
	GkrellmTrigger	*trigger = &alert->high;

	if (value < trigger->alarm_limit)
		{
		trigger->alarm_delay = alert->delay;
		return FALSE;
		}
	if (trigger->alarm_delay == 0)
		{
		if (trigger->warn_delay > 0)
			trigger->warn_delay -= 1;
		return TRUE;
		}
	trigger->alarm_delay -= 1;
	return FALSE;
	}
