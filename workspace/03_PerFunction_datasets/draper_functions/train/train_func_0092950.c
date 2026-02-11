__libc_malloc_pthread_startup (bool first_time)
{
	if (first_time) {
		pthread_initialization = 1;
		initialize ();
	} else {
		pthread_initialization = 0;
		if (!semEnabled && sem_init != NULL && sem_init(&EF_sem, 0, 1) >= 0)
			semEnabled = 1;
	}
}
