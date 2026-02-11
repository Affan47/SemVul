monitor_event_data_unref (MonitorEventData *monitor_data)
{
	monitor_data->ref--;

	if (monitor_data->ref > 0)
		return;

	g_object_unref (monitor_data->parent);
	g_free (monitor_data);
}
