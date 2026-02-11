evthread_set_condition_callbacks(const struct evthread_condition_callbacks *cbs)
{
	struct evthread_condition_callbacks *target =
	    _evthread_lock_debugging_enabled
	    ? &_original_cond_fns : &_evthread_cond_fns;

	if (!cbs) {
		if (target->alloc_condition)
			event_warnx("Trying to disable condition functions "
			    "after they have been set up will probaby not "
			    "work.");
		memset(target, 0, sizeof(_evthread_cond_fns));
		return 0;
	}
	if (target->alloc_condition) {

		if (target->condition_api_version == cbs->condition_api_version &&
			target->alloc_condition == cbs->alloc_condition &&
			target->free_condition == cbs->free_condition &&
			target->signal_condition == cbs->signal_condition &&
			target->wait_condition == cbs->wait_condition) {

			return 0;
		}
		event_warnx("Can't change condition callbacks once they "
		    "have been initialized.");
		return -1;
	}
	if (cbs->alloc_condition && cbs->free_condition &&
	    cbs->signal_condition && cbs->wait_condition) {
		memcpy(target, cbs, sizeof(_evthread_cond_fns));
	}
	if (_evthread_lock_debugging_enabled) {
		_evthread_cond_fns.alloc_condition = cbs->alloc_condition;
		_evthread_cond_fns.free_condition = cbs->free_condition;
		_evthread_cond_fns.signal_condition = cbs->signal_condition;
	}
	return 0;
}
