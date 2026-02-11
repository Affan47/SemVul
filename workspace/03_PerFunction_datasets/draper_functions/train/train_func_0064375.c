guess_final_stats(const guess_t *gq)
{
	tm_t end;

	guess_check(gq);

	tm_now_exact(&end);

	if (GNET_PROPERTY(guess_client_debug) > 1) {
		g_debug("GUESS QUERY[%s] \"%s\" took %g secs, "
			"queried_set=%zu, pool_set=%u, "
			"queried=%zu, acks=%zu, max_ultras=%zu, kept_results=%u/%u, "
			"out_qk=%u bytes, out_query=%u bytes",
			nid_to_string(&gq->gid),
			lazy_safe_search(gq->query),
			tm_elapsed_f(&end, &gq->start),
			hset_count(gq->queried),
			hash_list_length(gq->pool),
			gq->queried_nodes, gq->query_acks, gq->max_ultrapeers,
			gq->kept_results, gq->recv_results,
			gq->bw_out_qk, gq->bw_out_query);
	}
}
