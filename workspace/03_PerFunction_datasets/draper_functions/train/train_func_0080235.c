dispatcher_start_job (GiggleDispatcher *dispatcher, DispatcherJob *job)
{
	GiggleDispatcherPriv  *priv;
	gint                   argc;
	gchar                **argv;
	GError                *error = NULL;

	priv = GET_PRIV (dispatcher);

	g_assert (priv->current_job == NULL);

	if (!g_shell_parse_argv (job->command, &argc, &argv, &error)) {
		goto failed;
	}

	if (!g_spawn_async_with_pipes (job->wd, argv,
				       NULL,
				       G_SPAWN_SEARCH_PATH | G_SPAWN_DO_NOT_REAP_CHILD,
				       NULL, NULL,
				       &job->pid,
				       NULL, &job->std_out, &job->std_err,
				       &error)) {
		goto failed;
	}

	d(g_print ("GiggleDispatcher::run_job(job-started)\n"));

	priv->channel = g_io_channel_unix_new (job->std_out);
	g_io_channel_set_encoding (priv->channel, NULL, NULL);
	g_io_channel_set_flags (priv->channel,
	                        g_io_channel_get_flags (priv->channel)
	                        | G_IO_FLAG_NONBLOCK, NULL);
	priv->output = g_string_new ("");

	priv->current_job = job;
	priv->current_job_read_id = g_io_add_watch_full (priv->channel,
							 G_PRIORITY_HIGH_IDLE,
							 G_IO_IN,
							 (GIOFunc) dispatcher_job_read_cb,
							 dispatcher, NULL);
	priv->current_job_wait_id = g_child_watch_add (job->pid,
						       (GChildWatchFunc) dispatcher_job_finished_cb,
						       dispatcher);
	g_strfreev (argv);

	return TRUE;

failed:
	dispatcher_signal_job_failed (dispatcher, job, error);
	dispatcher_job_free (job);
	g_strfreev (argv);
	g_error_free (error);
	priv->current_job = NULL;
	priv->current_job_wait_id = 0;

	return FALSE;
}
