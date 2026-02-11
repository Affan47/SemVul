sgen_client_collecting_major_2 (void)
{
	if (profile_roots)
		notify_gc_roots (&major_root_report);

	if (mono_profiler_get_events () & MONO_PROFILE_GC_ROOTS)
		report_registered_roots ();
}
