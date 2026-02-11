trace_search_list(struct list_head **list)
{
	struct trace_event *e;
	int last = __TRACE_LAST_TYPE;

	if (list_empty(&ftrace_event_list)) {
		*list = &ftrace_event_list;
		return last + 1;
	}


	list_for_each_entry(e, &ftrace_event_list, list) {
		if (e->type != last + 1)
			break;
		last++;
	}


	if ((last + 1) > TRACE_EVENT_TYPE_MAX)
		return 0;

	*list = &e->list;
	return last + 1;
}
