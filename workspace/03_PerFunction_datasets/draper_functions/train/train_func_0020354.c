_e2_command_run_async (gchar *command, gchar **args, const gchar *cwd,
	gboolean show, gboolean extshell)
{
	printd (DEBUG, "asynchronously run command %s", command);
	_e2_command_block_childsignal ();

	if (cwd == NULL)
		cwd = curr_view->dir;
	gchar *local;
#ifdef E2_VFS


	local = (curr_view->spacedata == NULL) ?
		F_FILENAME_TO_LOCALE (cwd) : curr_view->spacedata->workplace;
#else
	local = F_FILENAME_TO_LOCALE (cwd);
#endif
	GPid pid = 0;
	gint stdinfd = 0, stdoutfd = 0, stderrfd = 0;
	GError *error = NULL;
	g_spawn_async_with_pipes (local, args, NULL,
		G_SPAWN_DO_NOT_REAP_CHILD | G_SPAWN_SEARCH_PATH,
		NULL, NULL, &pid, &stdinfd, &stdoutfd, &stderrfd, &error);
#ifdef E2_VFS
	if (curr_view->spacedata == NULL)
#endif
		F_FREE (local);


	if (error != NULL)
	{
		gchar *message = g_strconcat (extshell ? "sh>" : ">", command, " ", NULL);

		e2_output_print (&app.tab, message, NULL, TRUE, "bold", "blue", NULL);
		g_free (message);
		message = g_strconcat (error->message, ".", NULL);
		e2_output_print_error (message, TRUE);
		g_error_free (error);
		_e2_command_unblock_childsignal ();
		return 0;
	}

	E2_TaskRuntime *rt;

	while ((rt = e2_task_set_data ((glong)pid, E2_TASKTYPE_ASYNC, command)) == NULL);

	if (rt == GINT_TO_POINTER (1))
	{

		_e2_command_unblock_childsignal ();
		return 0;
	}
	rt->ex.command.show = show;
	rt->ex.command.extshell = extshell;


#if E2_DEBUG_LEVEL > 2
	stdoutchannel =
#endif
	_e2_command_setup_watch_channel (stdoutfd,
		G_IO_IN | G_IO_PRI | G_IO_HUP,
		_e2_command_watch_std, rt);

#if E2_DEBUG_LEVEL > 2
	stderrchannel =
#endif
	_e2_command_setup_watch_channel (stderrfd,
		G_IO_IN | G_IO_PRI | G_IO_ERR | G_IO_HUP | G_IO_NVAL,
		_e2_command_watch_err, rt);


	GIOChannel *ioc = g_io_channel_unix_new (stdinfd);
	g_io_channel_set_encoding (ioc, NULL, NULL);
	g_io_channel_set_buffered (ioc, FALSE);
	g_io_channel_set_close_on_unref (ioc, TRUE);


	rt->ex.command.to_child = ioc;

	if (show && e2_option_bool_get ("fileop-show"))
	{
		gchar *message = g_strconcat (extshell ? "sh>" : ">", command, NULL);
		e2_output_print (rt->current_tab, message, rt->pidstr, FALSE,
			"bold", "blue", NULL);
		g_free (message);
		message = g_strdup_printf ("  (%d)\n", pid);
		e2_output_print (rt->current_tab, message, rt->pidstr, FALSE,
			"small", "blue", NULL);
		g_free (message);
	}

	_e2_command_unblock_childsignal ();

	return pid;
}
