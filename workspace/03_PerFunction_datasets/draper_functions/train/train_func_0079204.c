timerbar_start_frame()
{
	timerbar_current_stack_layer = 0;
	timerbar_current_profile     = 0;

	if(QueryPerformanceCounter(&timerbar_ultimate_start_value) == FALSE)
	{

		draw_func_ptr = NULL;
	}

	timerbar_last_start_value = timerbar_ultimate_start_value;

}
