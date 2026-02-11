force_meminfo_update(void)
	{
	gint	i, force;

	force = force_update ? TRUE : FALSE;
	force_update = FALSE;
	if (GK.second_tick)
		{
		for (i = 1; i < PIPE_SIZE; ++i)
			if (mem_pipe[i] || swap_pipe[i])
				force = TRUE;
		if (_GK.cpu_sys_activity > 3)
			force = TRUE;
		}
	return force;
	}
