bury_pid( u_64 pid )
	{
	struct pid_cycles_item	*ptr;

	if( statspid>0 && pid == statspid )
		stop_taking_stats();

	if( printpid>0 && pid == printpid )
		printing = -1;

	for( ptr = pid_cycles_list; ptr; ptr = ptr->next )
		{
		if( ptr->pid == pid && !ptr->dead)
			{
			ptr->dead=1;
			break;
			}
		}


	}
