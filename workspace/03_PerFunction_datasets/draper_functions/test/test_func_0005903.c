wakeup_tracer_init(struct trace_array *tr)
{
	if (wakeup_busy)
		return -EBUSY;

	wakeup_dl = 0;
	wakeup_rt = 0;
	return __wakeup_tracer_init(tr);
}
