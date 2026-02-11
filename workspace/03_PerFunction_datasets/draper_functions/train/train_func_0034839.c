background_task_completed_cb (GthTask  *task,
			      GError   *error,
			      gpointer  user_data)
{
	TaskData   *task_data = user_data;
	GthBrowser *browser = task_data->browser;

	browser->priv->background_tasks = g_list_remove (browser->priv->background_tasks, task_data);
	task_data_free (task_data);

	if (error == NULL)
		return;

	if (! g_error_matches (error, GTH_TASK_ERROR, GTH_TASK_ERROR_CANCELLED) && ! g_error_matches (error, G_IO_ERROR, G_IO_ERROR_CANCELLED))
		_gth_browser_show_error (browser, _("Could not perform the operation"), error);
}
