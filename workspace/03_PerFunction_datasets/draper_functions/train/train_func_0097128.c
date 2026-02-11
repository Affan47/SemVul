mono_once (mono_once_t *once, void (*once_init) (void))
{
	int thr_ret;

	if (!once->complete) {
		pthread_cleanup_push ((void(*)(void *))pthread_mutex_unlock,
				      (void *)&once->mutex);
		thr_ret = pthread_mutex_lock (&once->mutex);
		g_assert (thr_ret == 0);

		if (!once->complete) {
			once_init ();
			once->complete = TRUE;
		}
		thr_ret = pthread_mutex_unlock (&once->mutex);
		g_assert (thr_ret == 0);

		pthread_cleanup_pop (0);
	}

	return 0;
}
