e2_command_kill_child (guint pid)
{
	E2_TaskRuntime *rt = e2_task_find_running_task ((glong)pid);
	if (!(rt == NULL || rt->action))
	{
		if (!kill ((pid_t) pid, SIGTERM))
		{
			rt->pid = -2L;
			rt->status = E2_TASK_ABORTED;
			return TRUE;
		}
		e2_output_print_strerrno ();
	}
	return FALSE;
}
