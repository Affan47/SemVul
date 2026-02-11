nmi_handle(unsigned int type, struct pt_regs *regs)
{
	struct nmi_desc *desc = nmi_to_desc(type);
	struct nmiaction *a;
	int handled=0;

	rcu_read_lock();


	list_for_each_entry_rcu(a, &desc->head, list) {
		int thishandled;
		u64 delta;

		delta = sched_clock();
		thishandled = a->handler(type, regs);
		handled += thishandled;
		delta = sched_clock() - delta;
		trace_nmi_handler(a->handler, (int)delta, thishandled);

		if (delta < nmi_longest_ns || delta < a->max_duration)
			continue;

		a->max_duration = delta;
		irq_work_queue(&a->irq_work);
	}

	rcu_read_unlock();


	return handled;
}
