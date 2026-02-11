e2_task_set_data (glong pid, E2_TaskDataType mode, gchar *command)
{
	static gboolean blocked = FALSE;
	if (blocked)
		return NULL;
	else
		blocked = TRUE;

	E2_TaskRuntime *rt = e2_task_find_running_task (pid);
	if (rt == NULL)
	{
		printd (DEBUG, "e2_task_set_data (pid:%d,mode:%d,command:%s)",
			pid, mode, command);
		rt = ALLOCATE (E2_TaskRuntime);
		CHECKALLOCATEDWARN (rt, )
		if (rt == NULL)
		{
			printd (WARN, "not enough memory for task history data");
			blocked = FALSE;
			return GINT_TO_POINTER (1);
		}
		if (mode == E2_TASKTYPE_ASYNC || mode == E2_TASKTYPE_SYNC)
		{
			rt->action = FALSE;
#ifndef E2_NEW_COMMAND
			rt->pid = pid;
#endif
			rt->ex.command.command = g_strdup (command);

			rt->ex.command.currdir = g_strdup (curr_view->dir);
#ifdef E2_COMMANDQ
			rt->ex.command.othrdir = g_strdup (other_view->dir);
# ifdef E2_VFS
			rt->ex.command.currspace = curr_view->spacedata;
			rt->ex.command.othrspace = other_view->spacedata;
# endif
			rt->ex.command.names = ;
			rt->ex.command.othernames = ;

#endif
#ifndef E2_NEW_COMMAND
			if (mode == E2_TASKTYPE_ASYNC)
			{
				rt->pidstr = g_strdup_printf ("%ld", rt->pid);

			}
			else
			{


				rt->pidstr = g_strdup_printf ("s%ld", -pid);
			}
			rt->status = E2_TASK_RUNNING;
#endif
		}
		else if (mode == E2_TASKTYPE_ACTION)
		{
			rt->action = TRUE;
			rt->status = E2_TASK_NONE;

			rt->ex.action.status = &rt->status;
		}
		else
		{
			printd (WARN, "tried to register a process with bad mode flag");
			DEALLOCATE (E2_TaskRuntime, rt);
			blocked = FALSE;
			return GINT_TO_POINTER (1);
		}


		rt->current_tab = &app.tab;
		rt->background_tab = curr_tab;

		pthread_mutex_lock (&task_mutex);
		app.taskhistory = g_list_append (app.taskhistory, rt);
		pthread_mutex_unlock (&task_mutex);
	}
	else
	{
		printd (DEBUG, "tried to re-register a process");
		blocked = FALSE;
		return GINT_TO_POINTER (1);
	}

	blocked = FALSE;
	return rt;
}
