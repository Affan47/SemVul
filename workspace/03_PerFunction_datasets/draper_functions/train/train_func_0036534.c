uprobe_dispatcher(struct uprobe_consumer *con, struct pt_regs *regs)
{
	struct trace_uprobe *tu;
	struct uprobe_dispatch_data udd;
	struct uprobe_cpu_buffer *ucb;
	int dsize, esize;
	int ret = 0;


	tu = container_of(con, struct trace_uprobe, consumer);
	tu->nhit++;

	udd.tu = tu;
	udd.bp_addr = instruction_pointer(regs);

	current->utask->vaddr = (unsigned long) &udd;

	if (WARN_ON_ONCE(!uprobe_cpu_buffer))
		return 0;

	dsize = __get_data_size(&tu->tp, regs);
	esize = SIZEOF_TRACE_ENTRY(is_ret_probe(tu));

	ucb = uprobe_buffer_get();
	store_trace_args(esize, &tu->tp, regs, ucb->buf, dsize);

	if (tu->tp.flags & TP_FLAG_TRACE)
		ret |= uprobe_trace_func(tu, regs, ucb, dsize);

#ifdef CONFIG_PERF_EVENTS
	if (tu->tp.flags & TP_FLAG_PROFILE)
		ret |= uprobe_perf_func(tu, regs, ucb, dsize);
#endif
	uprobe_buffer_put(ucb);
	return ret;
}
