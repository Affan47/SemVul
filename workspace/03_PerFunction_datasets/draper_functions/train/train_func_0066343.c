ao_tasks_update_single(AoTasks *t, GeanyDocument *cur_doc)
{
	AoTasksPrivate *priv = AO_TASKS_GET_PRIVATE(t);

	if (! priv->active)
		return;

	if (! priv->scan_all_documents)
	{

		gtk_list_store_clear(priv->store);
		ao_tasks_update(t, cur_doc);
	}
}
