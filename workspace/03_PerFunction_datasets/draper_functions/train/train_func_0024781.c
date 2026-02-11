_gck_call_async_short (GckCall *call, CK_RV rv)
{
	g_assert (GCK_IS_CALL (call));

	call->rv = rv;


	g_assert (GCK_CALL_GET_CLASS (call)->completed_queue);
	g_async_queue_push (GCK_CALL_GET_CLASS (call)->completed_queue, call);
	g_main_context_wakeup (NULL);
}
