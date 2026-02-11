mono_profiler_thread_start (gsize tid)
{
	ProfilerDesc *prof;
	for (prof = prof_list; prof; prof = prof->next) {
		if ((prof->events & MONO_PROFILE_THREADS) && prof->thread_start)
			prof->thread_start (prof->profiler, tid);
	}
}
