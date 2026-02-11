gitg_runner_stream_close (GitgRunner *runner,
                          GError     *error)
{
	g_return_if_fail (GITG_IS_RUNNER (runner));

	if (runner->priv->pid == 0 || error)
	{
		runner_done (runner, error);
	}
	else
	{
		g_input_stream_close (runner->priv->g_stdout, NULL, NULL);
	}
}
