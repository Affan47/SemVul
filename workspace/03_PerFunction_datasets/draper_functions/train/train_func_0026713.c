mono_profiler_install_gc (MonoProfileGCFunc callback, MonoProfileGCResizeFunc heap_resize_callback)
{
	mono_gc_enable_events ();
	if (!prof_list)
		return;
	prof_list->gc_event = callback;
	prof_list->gc_heap_resize = heap_resize_callback;
}
