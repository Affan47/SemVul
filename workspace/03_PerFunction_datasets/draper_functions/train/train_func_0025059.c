os_event_set(

	os_event_t	event)
{
	ut_a(event);

#ifdef __WIN__
	if (!srv_use_native_conditions) {
		ut_a(SetEvent(event->handle));
		return;
	}
#endif

	ut_a(event);

	os_fast_mutex_lock(&(event->os_mutex));

	if (event->is_set) {

	} else {
		event->is_set = TRUE;
		event->signal_count += 1;
		os_cond_broadcast(&(event->cond_var));
	}

	os_fast_mutex_unlock(&(event->os_mutex));
}
