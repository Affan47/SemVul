fr_process_clear (FrProcess *process)
{
	gint i;

	g_return_if_fail (process != NULL);

	for (i = 0; i <= process->priv->n_comm; i++) {
		FrCommandInfo *info;

		info = g_ptr_array_index (process->priv->comm, i);
		fr_command_info_free (info);
		g_ptr_array_index (process->priv->comm, i) = NULL;
	}

	for (i = 0; i <= process->priv->n_comm; i++)
		g_ptr_array_remove_index_fast (process->priv->comm, 0);

	process->priv->n_comm = -1;
	process->priv->current_comm = -1;
}
