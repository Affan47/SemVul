s_next(struct seq_file *m, void *v, loff_t *pos)
{
	struct trace_event_file *file = v;
	struct trace_array *tr = m->private;

	(*pos)++;

	list_for_each_entry_continue(file, &tr->events, list) {
		if (file->flags & EVENT_FILE_FL_ENABLED)
			return file;
	}

	return NULL;
}
