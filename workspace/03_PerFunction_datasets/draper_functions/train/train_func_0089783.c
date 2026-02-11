find_trace_kprobe(const char *event,
					      const char *group)
{
	struct trace_kprobe *tk;

	list_for_each_entry(tk, &probe_list, list)
		if (strcmp(trace_event_name(&tk->tp.call), event) == 0 &&
		    strcmp(tk->tp.call.class->system, group) == 0)
			return tk;
	return NULL;
}
