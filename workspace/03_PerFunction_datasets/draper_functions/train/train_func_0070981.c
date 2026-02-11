osq_lock(struct optimistic_spin_queue *lock)
{
	struct optimistic_spin_node *node = this_cpu_ptr(&osq_node);
	struct optimistic_spin_node *prev, *next;
	int curr = encode_cpu(smp_processor_id());
	int old;

	node->locked = 0;
	node->next = NULL;
	node->cpu = curr;


	old = atomic_xchg(&lock->tail, curr);
	if (old == OSQ_UNLOCKED_VAL)
		return true;

	prev = decode_cpu(old);
	node->prev = prev;
	WRITE_ONCE(prev->next, node);


	while (!READ_ONCE(node->locked)) {


		if (need_resched())
			goto unqueue;

		cpu_relax_lowlatency();
	}
	return true;

unqueue:


	for (;;) {
		if (prev->next == node &&
		    cmpxchg(&prev->next, node, NULL) == node)
			break;


		if (smp_load_acquire(&node->locked))
			return true;

		cpu_relax_lowlatency();


		prev = READ_ONCE(node->prev);
	}


	next = osq_wait_next(lock, node, prev);
	if (!next)
		return false;


	WRITE_ONCE(next->prev, prev);
	WRITE_ONCE(prev->next, next);

	return false;
}
