hs_update (void)
{
	if (state.mem_range)
	{
		if (!state.hiscores_have_been_loaded)
		{
			if (safe_to_load()) hs_load();
		}
	}
}
