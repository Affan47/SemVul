g_resolv_unref(GResolv *resolv)
{
	struct resolv_query *query;
	struct resolv_lookup *lookup;

	if (resolv == NULL)
		return;

	if (__sync_fetch_and_sub(&resolv->ref_count, 1) != 1)
		return;

	while ((lookup = g_queue_pop_head(resolv->lookup_queue))) {
		debug(resolv, "lookup %p id %d", lookup, lookup->id);
		destroy_lookup(lookup);
	}

	while ((query = g_queue_pop_head(resolv->query_queue))) {
		debug(resolv, "query %p", query);
		destroy_query(query);
	}

	g_queue_free(resolv->query_queue);
	g_queue_free(resolv->lookup_queue);

	flush_nameservers(resolv);

	res_nclose(&resolv->res);

	g_free(resolv);
}
