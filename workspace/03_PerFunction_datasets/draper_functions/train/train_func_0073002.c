__trace_early_add_event_dirs(struct trace_array *tr)
{
	struct trace_event_file *file;
	int ret;


	list_for_each_entry(file, &tr->events, list) {
		ret = event_create_dir(tr->event_dir, file);
		if (ret < 0)
			pr_warn("Could not create directory for event %s\n",
				trace_event_name(file->event_call));
	}
}
