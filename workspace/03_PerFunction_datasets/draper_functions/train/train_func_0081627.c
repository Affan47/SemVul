count_states(int states)
{
	if (!micro.timer)
	{
		timer_adjust(micro.timer, TIME_NEVER, 0, 0);
		micro.timer_active = 1;
		micro.endtime = (double)states * MICRO_STATE_CLOCK_PERIOD;
	}
	else if (timer_timeelapsed(micro.timer) > micro.endtime)
	{
		timer_adjust(micro.timer, TIME_NEVER, 0, 0);
		micro.timer_active = 1;
		micro.endtime = (double)states * MICRO_STATE_CLOCK_PERIOD;
	}
	else
		micro.endtime += (double)states * MICRO_STATE_CLOCK_PERIOD;
}
