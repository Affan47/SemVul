sgen_client_collecting_minor (SgenPointerQueue *fin_ready_queue, SgenPointerQueue *critical_fin_queue)
{
	if (mono_profiler_get_events () & MONO_PROFILE_GC_ROOTS)
		report_registered_roots ();
	if (mono_profiler_get_events () & MONO_PROFILE_GC_ROOTS)
		report_finalizer_roots (fin_ready_queue, critical_fin_queue);
}
