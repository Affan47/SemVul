__mutex_trylock_slowpath(atomic_t *lock_count)
{
	struct mutex *lock = container_of(lock_count, struct mutex, count);
	unsigned long flags;
	int prev;


	if (mutex_is_locked(lock))
		return 0;

	spin_lock_mutex(&lock->wait_lock, flags);

	prev = atomic_xchg_acquire(&lock->count, -1);
	if (likely(prev == 1)) {
		mutex_set_owner(lock);
		mutex_acquire(&lock->dep_map, 0, 1, _RET_IP_);
	}


	if (likely(list_empty(&lock->wait_list)))
		atomic_set(&lock->count, 0);

	spin_unlock_mutex(&lock->wait_lock, flags);

	return prev == 1;
}
