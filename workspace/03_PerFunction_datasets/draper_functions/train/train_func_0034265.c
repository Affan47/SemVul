async_context_free (AsyncContext *async_context)
{
	if (async_context->authenticator != NULL)
		g_object_unref (async_context->authenticator);

	if (async_context->signon_auth_session != NULL)
		g_object_unref (async_context->signon_auth_session);

	if (async_context->ag_auth_data != NULL)
		ag_auth_data_unref (async_context->ag_auth_data);

	if (async_context->cancellable != NULL)
		g_object_unref (async_context->cancellable);

	g_slice_free (AsyncContext, async_context);
}
