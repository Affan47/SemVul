__available_for_read(struct block_lock *lock)
{
	return lock->count >= 0 &&
		lock->count < MAX_HOLDERS &&
		list_empty(&lock->waiters);
}
