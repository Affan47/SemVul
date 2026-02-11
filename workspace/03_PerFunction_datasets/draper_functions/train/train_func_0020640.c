trace_find_event_field(struct trace_event_call *call, char *name)
{
	struct ftrace_event_field *field;
	struct list_head *head;

	head = trace_get_fields(call);
	field = __find_event_field(head, name);
	if (field)
		return field;

	field = __find_event_field(&ftrace_generic_fields, name);
	if (field)
		return field;

	return __find_event_field(&ftrace_common_fields, name);
}
