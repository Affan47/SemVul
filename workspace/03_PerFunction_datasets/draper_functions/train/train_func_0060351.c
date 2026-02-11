scan_task_region (GtkSourceSearchContext *search)
{
	ForwardBackwardData *task_data = g_task_get_task_data (search->priv->task);

	if (task_data->is_forward)
	{
		scan_region_forward (search, search->priv->task_region);
	}
	else
	{
		scan_region_backward (search, search->priv->task_region);
	}

	resume_task (search);
}
