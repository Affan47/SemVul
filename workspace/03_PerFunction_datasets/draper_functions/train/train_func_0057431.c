secret_search_unlock_load_or_complete (GSimpleAsyncResult *async,
                                       SearchClosure *search)
{
	GList *items;


	if (search->flags & SECRET_SEARCH_UNLOCK) {
		items = search_closure_build_items (search, search->locked);
		secret_service_unlock (search->service, items, search->cancellable,
		                       on_search_unlocked, g_object_ref (async));
		g_list_free_full (items, g_object_unref);


	} else if (search->flags & SECRET_SEARCH_LOAD_SECRETS) {
		items = g_hash_table_get_values (search->items);
		secret_item_load_secrets (items, search->cancellable,
		                          on_search_secrets, g_object_ref (async));
		g_list_free (items);


	} else {
		g_simple_async_result_complete (async);
	}
}
