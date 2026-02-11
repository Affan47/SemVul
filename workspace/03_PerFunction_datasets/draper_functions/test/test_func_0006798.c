perf_callchain(struct perf_event *event, struct pt_regs *regs)
{
	int rctx;
	struct perf_callchain_entry *entry;

	int kernel = !event->attr.exclude_callchain_kernel;
	int user   = !event->attr.exclude_callchain_user;

	if (!kernel && !user)
		return NULL;

	entry = get_callchain_entry(&rctx);
	if (rctx == -1)
		return NULL;

	if (!entry)
		goto exit_put;

	entry->nr = 0;

	if (kernel && !user_mode(regs)) {
		perf_callchain_store(entry, PERF_CONTEXT_KERNEL);
		perf_callchain_kernel(entry, regs);
	}

	if (user) {
		if (!user_mode(regs)) {
			if  (current->mm)
				regs = task_pt_regs(current);
			else
				regs = NULL;
		}

		if (regs) {


			if (event->ctx->task && event->ctx->task != current)
				goto exit_put;

			perf_callchain_store(entry, PERF_CONTEXT_USER);
			perf_callchain_user(entry, regs);
		}
	}

exit_put:
	put_callchain_entry(rctx);

	return entry;
}
