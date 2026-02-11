pthread_create_and_store (string name, pthread_t  *thread, pthread_attr_t *attr, void * (*start_routine)(void *), void * arg)
{
	int ret;

	pthread_attr_t default_attr;
	bool use_default_attr = (attr == NULL);

	if (use_default_attr) {

		pthread_attr_init(&default_attr);
		pthread_attr_setstacksize(&default_attr, 500000);
		attr = &default_attr;
	}

	if ((ret = thread_creator (thread, attr, start_routine, arg)) == 0) {
		std::pair<string,pthread_t> newpair;
		newpair.first = name;
		newpair.second = *thread;

		pthread_mutex_lock (&thread_map_lock);
		all_threads.insert (newpair);

		pthread_mutex_unlock (&thread_map_lock);
	}

	if (use_default_attr) {
		pthread_attr_destroy(&default_attr);
	}

	return ret;
}
