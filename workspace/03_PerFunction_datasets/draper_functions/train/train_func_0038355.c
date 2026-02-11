on_debug_terminate(const MenuItem *menu_item)
{
	switch (debug_state())
	{
		case DS_DEBUG :
		case DS_READY :
		{
			if (menu_item && !debug_auto_exit)
			{
				debug_send_command(N, "kill");
				break;
			}
		}
		case DS_HANGING :
		{
			gdb_exit();
			break;
		}
		default :
		{
			gdb_state = KILLING;
			if (kill(gdb_pid, SIGKILL) == -1)
				show_errno("kill(gdb)");
		}
	}
}
