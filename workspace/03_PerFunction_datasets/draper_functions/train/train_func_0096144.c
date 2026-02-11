check_cancellable_cb (gpointer user_data)
{
	CancelData *cancel_data = user_data;
	GthBrowser *browser = cancel_data->browser;

	if ((browser->priv->load_data_queue == NULL)
	    && (browser->priv->load_file_data_queue == NULL)
	    && (browser->priv->task == NULL)
	    && (browser->priv->background_tasks == NULL))
	{
		g_source_remove (cancel_data->check_id);
		cancel_data->check_id = 0;

		if (cancel_data->done_func != NULL)
			cancel_data->done_func (cancel_data->user_data);
		cancel_data_unref (cancel_data);

		return FALSE;
	}

	return TRUE;
}
