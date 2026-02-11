heap_walk (MonoProfiler *profiler)
{
	int do_walk = 0;
	uint64_t now;
	LogBuffer *logbuffer;
	if (!do_heap_shot)
		return;
	logbuffer = ensure_logbuf (10);
	now = current_time ();
	if (hs_mode_ms && (now - last_hs_time)/1000000 >= hs_mode_ms)
		do_walk = 1;
	else if (hs_mode_gc && (gc_count % hs_mode_gc) == 0)
		do_walk = 1;
	else if (hs_mode_ondemand)
		do_walk = heapshot_requested;
	else if (!hs_mode_ms && !hs_mode_gc && profiler->last_gc_gen_started == mono_gc_max_generation ())
		do_walk = 1;

	if (!do_walk)
		return;
	heapshot_requested = 0;
	emit_byte (logbuffer, TYPE_HEAP_START | TYPE_HEAP);
	emit_time (logbuffer, now);
	mono_gc_walk_heap (0, gc_reference, NULL);
	logbuffer = ensure_logbuf (10);
	now = current_time ();
	emit_byte (logbuffer, TYPE_HEAP_END | TYPE_HEAP);
	emit_time (logbuffer, now);
	last_hs_time = now;
}
