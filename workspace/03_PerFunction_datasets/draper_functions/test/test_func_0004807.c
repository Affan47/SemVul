event_enable_print(struct seq_file *m, unsigned long ip,
		      struct ftrace_probe_ops *ops, void *_data)
{
	struct event_probe_data *data = _data;

	seq_printf(m, "%ps:", (void *)ip);

	seq_printf(m, "%s:%s:%s",
		   data->enable ? ENABLE_EVENT_STR : DISABLE_EVENT_STR,
		   data->file->event_call->class->system,
		   trace_event_name(data->file->event_call));

	if (data->count == -1)
		seq_puts(m, ":unlimited\n");
	else
		seq_printf(m, ":count=%ld\n", data->count);

	return 0;
}
