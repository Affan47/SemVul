evthread_set_locking_callback(void (*locking_fn)(int mode, void *lock))
{
	api_warn();
	if (locking_fn) {
		_evthread_lock_fns.lock = compat_lock_lock;
		_evthread_lock_fns.unlock = compat_lock_unlock;
	} else {
		_evthread_lock_fns.lock = NULL;
		_evthread_lock_fns.unlock = NULL;
	}
	_obsolete_locking_fn = locking_fn;
}
