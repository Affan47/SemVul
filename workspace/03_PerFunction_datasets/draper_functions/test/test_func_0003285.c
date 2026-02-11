join_workers (void)
{
	if (concurrent_collection_in_progress || major_collector.is_parallel) {
		gray_queue_redirect (&gray_queue);
		sgen_workers_join ();
	}

	g_assert (sgen_gray_object_queue_is_empty (&gray_queue));

#ifdef SGEN_DEBUG_INTERNAL_ALLOC
	main_gc_thread = NULL;
#endif
}
