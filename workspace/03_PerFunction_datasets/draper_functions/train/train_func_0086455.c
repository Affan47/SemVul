process_result (GckCall *call, gpointer unused)
{
	gboolean stop = FALSE;


	g_assert (GCK_IS_CALL (call));

	if (call->cancellable) {

		if (g_cancellable_is_cancelled (call->cancellable)) {
			call->rv = CKR_FUNCTION_CANCELED;
			stop = TRUE;
		}
	}


	if (!stop && !complete_call (call->complete, call->args, call->rv)) {
		g_object_ref (call);
		g_thread_pool_push (GCK_CALL_GET_CLASS (call)->thread_pool, call, NULL);


	} else if (call->callback) {
		(call->callback) (call->object, G_ASYNC_RESULT (call),
				  call->user_data);
	}
}
