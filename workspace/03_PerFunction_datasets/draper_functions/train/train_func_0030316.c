mono_profiler_runtime_initialized (void) {
	ProfilerDesc *prof;
	for (prof = prof_list; prof; prof = prof->next) {
		if (prof->runtime_initialized_event)
			prof->runtime_initialized_event (prof->profiler);
	}
}
