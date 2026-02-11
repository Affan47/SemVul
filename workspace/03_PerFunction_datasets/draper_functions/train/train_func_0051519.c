fluid_rvoice_mixer_set_threads(fluid_rvoice_mixer_t* mixer, int thread_count,
                               int prio_level)
{
#ifdef ENABLE_MIXER_THREADS
	char name[16];
	int i;


	if (mixer->thread_count) {
		fluid_atomic_int_set(&mixer->threads_should_terminate, 1);

		fluid_cond_mutex_lock(mixer->wakeup_threads_m);
		for (i=0; i < mixer->thread_count; i++)
			fluid_atomic_int_set(&mixer->threads[i].ready, THREAD_BUF_TERMINATE);
		fluid_cond_broadcast(mixer->wakeup_threads);
		fluid_cond_mutex_unlock(mixer->wakeup_threads_m);

		for (i=0; i < mixer->thread_count; i++) {
			if (mixer->threads[i].thread) {
				fluid_thread_join(mixer->threads[i].thread);
				delete_fluid_thread(mixer->threads[i].thread);
			}
			fluid_mixer_buffers_free(&mixer->threads[i]);
		}
		FLUID_FREE(mixer->threads);
		mixer->thread_count = 0;
		mixer->threads = NULL;
	}

	if (thread_count == 0)
		return;


	fluid_atomic_int_set(&mixer->threads_should_terminate, 0);
	mixer->threads = FLUID_ARRAY(fluid_mixer_buffers_t, thread_count);
	if (mixer->threads == NULL) {
		FLUID_LOG(FLUID_ERR, "Out of memory");
		return;
	}
	FLUID_MEMSET(mixer->threads, 0, thread_count*sizeof(fluid_mixer_buffers_t));
	mixer->thread_count = thread_count;
	for (i=0; i < thread_count; i++) {
		fluid_mixer_buffers_t* b = &mixer->threads[i];
		if (!fluid_mixer_buffers_init(b, mixer))
			return;
		fluid_atomic_int_set(&b->ready, THREAD_BUF_NODATA);
		snprintf (name, sizeof (name), "mixer%d", i);
		b->thread = new_fluid_thread(name, fluid_mixer_thread_func, b, prio_level, 0);
		if (!b->thread)
			return;
	}

#endif
}
