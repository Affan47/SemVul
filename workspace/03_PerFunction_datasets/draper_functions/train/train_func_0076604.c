query_timeout(gpointer user_data)
{
	struct resolv_query *query = user_data;
	struct resolv_lookup *lookup = query->lookup;
	GResolv *resolv = query->resolv;

	query->timeout = 0;

	if (query == lookup->ipv4_query) {
		lookup->ipv4_status = G_RESOLV_RESULT_STATUS_NO_RESPONSE;
		lookup->ipv4_query = NULL;
	} else if (query == lookup->ipv6_query) {
		lookup->ipv6_status = G_RESOLV_RESULT_STATUS_NO_RESPONSE;
		lookup->ipv6_query = NULL;
	}

	g_queue_remove(resolv->query_queue, query);
	destroy_query(query);

	if (lookup->ipv4_query == NULL && lookup->ipv6_query == NULL)
		sort_and_return_results(lookup);

	return FALSE;
}
