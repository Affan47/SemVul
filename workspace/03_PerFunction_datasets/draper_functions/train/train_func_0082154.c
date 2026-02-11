nm_dispatcher_call_cancel (gconstpointer call)
{


	if (g_slist_find (requests, call))
		((DispatchInfo *) call)->callback = NULL;
}
