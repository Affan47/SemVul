agmt_schedule_in_window_now(const Repl_Agmt *ra)
{
	int return_value;
	PR_ASSERT(NULL != ra);
	PR_Lock(ra->lock);
	if (NULL != ra->schedule && schedule_in_window_now(ra->schedule))
	{
		return_value = 1;
	}
	else
	{
		return_value = 0;
	}
	PR_Unlock(ra->lock);
	return return_value;
}
