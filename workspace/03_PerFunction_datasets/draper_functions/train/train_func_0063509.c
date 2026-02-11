malloc_mutex_init(malloc_mutex_t *mutex)
{

#ifdef _WIN32
	if (!InitializeCriticalSectionAndSpinCount(&mutex->lock,
	    _CRT_SPINCOUNT))
		return (true);
#elif (defined(JEMALLOC_OSSPIN))
	mutex->lock = 0;
#elif (defined(JEMALLOC_MUTEX_INIT_CB))
	if (postpone_init) {
		mutex->postponed_next = postponed_mutexes;
		postponed_mutexes = mutex;
	} else {
		if (_pthread_mutex_init_calloc_cb(&mutex->lock, base_calloc) !=
		    0)
			return (true);
	}
#else
	pthread_mutexattr_t attr;

	if (pthread_mutexattr_init(&attr) != 0)
		return (true);
	pthread_mutexattr_settype(&attr, MALLOC_MUTEX_TYPE);
	if (pthread_mutex_init(&mutex->lock, &attr) != 0) {
		pthread_mutexattr_destroy(&attr);
		return (true);
	}
	pthread_mutexattr_destroy(&attr);
#endif
	return (false);
}
