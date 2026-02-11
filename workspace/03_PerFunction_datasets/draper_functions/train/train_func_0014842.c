_gck_call_async_go (GckCall *call)
{
	g_assert (GCK_IS_CALL (call));


	process_completed(GCK_CALL_GET_CLASS (call));

	g_assert (GCK_CALL_GET_CLASS (call)->thread_pool);
	g_thread_pool_push (GCK_CALL_GET_CLASS (call)->thread_pool, call, NULL);
}
