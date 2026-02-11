irq_work_claim(struct irq_work *work)
{
	unsigned long flags, oflags, nflags;


	flags = work->flags & ~IRQ_WORK_PENDING;
	for (;;) {
		nflags = flags | IRQ_WORK_FLAGS;
		oflags = cmpxchg(&work->flags, flags, nflags);
		if (oflags == flags)
			break;
		if (oflags & IRQ_WORK_PENDING)
			return false;
		flags = oflags;
		cpu_relax();
	}

	return true;
}
