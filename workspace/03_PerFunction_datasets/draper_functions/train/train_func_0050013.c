add_history_(enum failtest_call_type type,
					  bool can_leak,
					  const char *file,
					  unsigned int line,
					  const void *elem,
					  size_t elem_size)
{
	struct failtest_call *call;


	if (!file)
		return &unrecorded_call;

	call = malloc(sizeof *call);
	call->type = type;
	call->can_leak = can_leak;
	call->file = file;
	call->line = line;
	call->cleanup = NULL;
	call->backtrace = get_backtrace(&call->backtrace_num);
	memcpy(&call->u, elem, elem_size);
	tlist_add_tail(&history, call, list);
	return call;
}
