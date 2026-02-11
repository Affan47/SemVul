e2_task_drop (E2_TaskType type, gchar *s_local, gchar *d_local,
	GPtrArray *names_local)
{

	if (strcmp (s_local, d_local) == 0)
		return FALSE;


	srcdir_local = s_local;
	destdir_local = d_local;
	names_array = names_local;

	gchar *action_name;
	gboolean result;
	gpointer taskfunc;
	switch (type)
	{
		case E2_TASK_LINK:
			action_name = g_strconcat (_A(5),".",_A(91),NULL);
			taskfunc = _e2_task_symlinkQ;
			break;
		case E2_TASK_MOVE:
			action_name = g_strconcat (_A(5),".",_A(58),NULL);
			taskfunc = _e2_task_moveQ;
			break;
		default:

			action_name = g_strconcat (_A(5),".",_A(33),NULL);
			taskfunc = _e2_task_copyQ;
			break;
	}

	E2_Action *action = e2_action_get (action_name);
	E2_ActionRuntime *art = e2_action_pack_runtime (action, NULL, NULL);

	result = e2_task_run_task (type, art, NULL, taskfunc, e2_task_refresh_lists,
		FALSE, FALSE);

	g_free (action_name);
	e2_action_free_runtime (art);

	if (!result)
		return FALSE;

	result = _e2_task_wait (NULL);
	return result;
}
