brasero_task_reset (BraseroTask *task)
{
	BraseroTaskPrivate *priv;

	priv = BRASERO_TASK_PRIVATE (task);

	if (brasero_task_is_running (task))
		brasero_task_cancel (task, TRUE);

	g_object_unref (priv->leader);
	brasero_task_reset_real (task);
}
