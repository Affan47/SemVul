runtime_initialized (MonoProfiler *prof)
{
	process_profiler_event (EVENT_KIND_VM_START, mono_thread_current ());
	if (agent_config.defer)
		start_debugger_thread ();
}
