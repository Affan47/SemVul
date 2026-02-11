__ftrace_set_clr_event_nolock(struct trace_array *tr, const char *match,
			      const char *sub, const char *event, int set)
{
	struct trace_event_file *file;
	struct trace_event_call *call;
	const char *name;
	int ret = -EINVAL;

	list_for_each_entry(file, &tr->events, list) {

		call = file->event_call;
		name = trace_event_name(call);

		if (!name || !call->class || !call->class->reg)
			continue;

		if (call->flags & TRACE_EVENT_FL_IGNORE_ENABLE)
			continue;

		if (match &&
		    strcmp(match, name) != 0 &&
		    strcmp(match, call->class->system) != 0)
			continue;

		if (sub && strcmp(sub, call->class->system) != 0)
			continue;

		if (event && strcmp(event, name) != 0)
			continue;

		ftrace_event_enable_disable(file, set);

		ret = 0;
	}

	return ret;
}
