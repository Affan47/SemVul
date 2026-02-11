timerbar_switch_type(int num)
{
	if(num >= MAX_NUM_TIMERBARS)
	{
		return;
	}


	LARGE_INTEGER now;
	if(QueryPerformanceCounter(&now) == FALSE)
	{

	}

	profiles[timerbar_current_profile].frame_total.QuadPart +=
		(now.QuadPart - timerbar_last_start_value.QuadPart);

	if(num != -1)
	{

		timerbar_current_profile = num;
	}


	if(QueryPerformanceCounter(&timerbar_last_start_value) == FALSE)
	{

	}
}
