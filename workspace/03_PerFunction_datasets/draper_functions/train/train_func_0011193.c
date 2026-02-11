pk_spawn_finalize (GObject *object)
{
	PkSpawn *spawn;

	g_return_if_fail (object != NULL);
	g_return_if_fail (PK_IS_SPAWN (object));

	spawn = PK_SPAWN (object);

	g_return_if_fail (spawn->priv != NULL);


	if (spawn->priv->poll_id != 0) {
		g_source_remove (spawn->priv->poll_id);
		spawn->priv->poll_id = 0;
	}


	if (spawn->priv->kill_id != 0) {
		g_source_remove (spawn->priv->kill_id);
		spawn->priv->kill_id = 0;
	}


	if (spawn->priv->stdin_fd != -1) {
		g_debug ("killing as still running in finalize");
		pk_spawn_kill (spawn);

		if (spawn->priv->kill_id != 0)
			g_source_remove (spawn->priv->kill_id);
	}


	g_string_free (spawn->priv->stdout_buf, TRUE);
	g_string_free (spawn->priv->stderr_buf, TRUE);
	g_free (spawn->priv->last_argv0);
	g_strfreev (spawn->priv->last_envp);
	g_object_unref (spawn->priv->conf);

	G_OBJECT_CLASS (pk_spawn_parent_class)->finalize (object);
}
