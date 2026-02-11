giggle_git_config_update (GiggleGitConfig     *config,
			  GiggleGitConfigFunc  func,
			  gpointer             data)
{
	GiggleGitConfigPriv *priv;
	GiggleGitConfigTask *task;

	g_return_if_fail (GIGGLE_IS_GIT_CONFIG (config));

	priv = GET_PRIV (config);

	if (priv->current_job) {
		giggle_git_cancel_job (priv->git, priv->current_job);
		g_object_unref (priv->current_job);
		priv->current_job = NULL;
	}

	if (priv->config) {

		g_hash_table_remove_all (priv->config);
	}

	task = g_new0 (GiggleGitConfigTask, 1);
	task->func = func;
	task->data = data;
	task->config = config;

	priv->current_job = giggle_git_config_read_new ();

	giggle_git_run_job_full (priv->git, priv->current_job,
				 git_config_read_cb, task, g_free);
}
