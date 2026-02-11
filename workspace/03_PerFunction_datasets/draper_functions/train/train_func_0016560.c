async_context_free (AsyncContext *async_context)
{
	if (async_context->client_view != NULL)
		g_object_unref (async_context->client_view);

	if (async_context->in_comp != NULL)
		icalcomponent_free (async_context->in_comp);

	if (async_context->out_comp != NULL)
		icalcomponent_free (async_context->out_comp);

	if (async_context->zone != NULL)
		icaltimezone_free (async_context->zone, 1);

	g_slist_free_full (
		async_context->comp_list,
		(GDestroyNotify) icalcomponent_free);

	g_slist_free_full (
		async_context->object_list,
		(GDestroyNotify) g_object_unref);

	g_slist_free_full (
		async_context->string_list,
		(GDestroyNotify) g_free);

	g_free (async_context->sexp);
	g_free (async_context->tzid);
	g_free (async_context->uid);
	g_free (async_context->rid);
	g_free (async_context->auid);

	g_slice_free (AsyncContext, async_context);
}
