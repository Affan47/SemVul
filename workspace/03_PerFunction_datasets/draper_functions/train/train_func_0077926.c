check_prevs_add(struct task_struct *curr, struct held_lock *next)
{
	int depth = curr->lockdep_depth;
	int trylock_loop = 0;
	struct held_lock *hlock;


	if (!depth)
		goto out_bug;


	if (curr->held_locks[depth].irq_context !=
			curr->held_locks[depth-1].irq_context)
		goto out_bug;

	for (;;) {
		int distance = curr->lockdep_depth - depth + 1;
		hlock = curr->held_locks + depth - 1;


		if (hlock->read != 2 && hlock->check) {
			if (!check_prev_add(curr, hlock, next,
						distance, trylock_loop))
				return 0;


			if (!hlock->trylock)
				break;
		}
		depth--;


		if (!depth)
			break;


		if (curr->held_locks[depth].irq_context !=
				curr->held_locks[depth-1].irq_context)
			break;
		trylock_loop = 1;
	}
	return 1;
out_bug:
	if (!debug_locks_off_graph_unlock())
		return 0;


	WARN_ON(1);

	return 0;
}
