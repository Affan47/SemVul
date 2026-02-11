async_context_free (AsyncContext *async_context)
{
	if (async_context->cancellable != NULL) {
		g_cancellable_disconnect (
			async_context->cancellable,
			async_context->cancel_id);
		g_object_unref (async_context->cancellable);
	}

	if (async_context->timeout_id > 0)
		g_source_remove (async_context->timeout_id);

	g_slice_free (AsyncContext, async_context);
}
