gda_threader_dispose (GObject   * object)
{
	GdaThreader *thread;

	g_return_if_fail (object != NULL);
	g_return_if_fail (GDA_IS_THREADER (object));

	thread = GDA_THREADER (object);
	if (thread->priv) {
		if (thread->priv->idle_func_id) {
			g_idle_remove_by_data (thread);
			thread->priv->idle_func_id = 0;
		}

		if (thread->priv->nb_jobs > 0) {

			thread->priv->nb_jobs = 0;
		}

		if (thread->priv->jobs) {
			g_hash_table_destroy (thread->priv->jobs);
			thread->priv->jobs = NULL;
		}
	}


	parent_class->dispose (object);
}
