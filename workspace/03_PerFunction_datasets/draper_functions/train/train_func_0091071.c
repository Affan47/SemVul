atomic_dec_and_mutex_lock(atomic_t *cnt, struct mutex *lock)
{

	if (atomic_add_unless(cnt, -1, 1))
		return 0;

	mutex_lock(lock);
	if (!atomic_dec_and_test(cnt)) {

		mutex_unlock(lock);
		return 0;
	}

	return 1;
}
