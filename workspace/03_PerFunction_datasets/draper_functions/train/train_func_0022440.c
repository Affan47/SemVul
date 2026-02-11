rb_profiler_free (RBProfiler *profiler)
{
	if (debug_match == NULL)
		return;
	if (profiler == NULL)
		return;

	g_timer_destroy (profiler->timer);
	g_free (profiler->name);
	g_free (profiler);
}
