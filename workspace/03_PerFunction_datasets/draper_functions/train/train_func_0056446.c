reset_file_list (NemoSearchDirectory *search)
{
	GList *list, *monitor_list;
	NemoFile *file;
	SearchMonitor *monitor;


	for (list = search->details->files; list != NULL; list = list->next) {
		file = list->data;


		g_signal_handlers_disconnect_by_func (file, file_changed, search);


		for (monitor_list = search->details->monitor_list; monitor_list;
		     monitor_list = monitor_list->next) {
			monitor = monitor_list->data;
			nemo_file_monitor_remove (file, monitor);
		}
	}

	nemo_file_list_free (search->details->files);
	search->details->files = NULL;
}
