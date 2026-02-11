add_trace_thread (ThreadContext *thread, TraceDesc *trace, uint64_t value)
{
	BackTrace *bt;
	int count = thread->stack_id;
	if (!collect_traces)
		return NULL;
	if (count > trace_max)
		count = trace_max;
	bt = add_backtrace (count, thread->stack + thread->stack_id - count);
	add_trace_bt (bt, trace, value);
	return bt;
}
