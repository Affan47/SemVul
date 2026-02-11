logthread_object(bool once)
{
	logthread_t *lt;

	lt = thread_private_get(func_to_pointer(logthread_object));

	if G_UNLIKELY(NULL == lt) {
		lt = log_thread_alloc();
		if (!once)
			thread_private_add(func_to_pointer(logthread_object), lt);
	}

	logthread_check(lt);

	return lt;
}
