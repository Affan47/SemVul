__task_wakeup(struct task *t)
{
	run_queue++;
	t->rq.key = ++rqueue_ticks;

	if (likely(t->nice)) {
		int offset;

		niced_tasks++;
		if (likely(t->nice > 0))
			offset = (unsigned)((run_queue * (unsigned int)t->nice) / 32U);
		else
			offset = -(unsigned)((run_queue * (unsigned int)-t->nice) / 32U);
		t->rq.key += offset;
	}


	t->state &= ~TASK_WOKEN_ANY;

	eb32_insert(&rqueue, &t->rq);
	return t;
}
