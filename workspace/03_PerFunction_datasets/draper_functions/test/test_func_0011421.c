dir_changed (GFileMonitor* monitor,
	     GFile *child,
	     GFile *other_file,
	     GFileMonitorEvent event_type,
	     gpointer user_data)
{
	char *uri, *to_uri;

	uri = g_file_get_uri (child);
	to_uri = NULL;
	if (other_file) {
		to_uri = g_file_get_uri (other_file);
	}

	switch (event_type) {
	default:
	case G_FILE_MONITOR_EVENT_CHANGED:

		break;
	case G_FILE_MONITOR_EVENT_ATTRIBUTE_CHANGED:
	case G_FILE_MONITOR_EVENT_CHANGES_DONE_HINT:
		nautilus_file_changes_queue_file_changed (child);
		break;
	case G_FILE_MONITOR_EVENT_UNMOUNTED:
	case G_FILE_MONITOR_EVENT_DELETED:
		nautilus_file_changes_queue_file_removed (child);
		break;
	case G_FILE_MONITOR_EVENT_CREATED:
		nautilus_file_changes_queue_file_added (child);
		break;
	}

	g_free (uri);
	g_free (to_uri);

	schedule_call_consume_changes ();
}
