lock_contended(struct lockdep_map *lock, unsigned long ip)
{
	unsigned long flags;

	if (unlikely(!lock_stat))
		return;

	if (unlikely(current->lockdep_recursion))
		return;

	raw_local_irq_save(flags);
	check_flags(flags);
	current->lockdep_recursion = 1;
	trace_lock_contended(lock, ip);
	__lock_contended(lock, ip);
	current->lockdep_recursion = 0;
	raw_local_irq_restore(flags);
}
