do_raw_spin_lock(raw_spinlock_t *lock)
{
	debug_spin_lock_before(lock);
	if (unlikely(!arch_spin_trylock(&lock->raw_lock)))
		__spin_lock_debug(lock);
	debug_spin_lock_after(lock);
}
