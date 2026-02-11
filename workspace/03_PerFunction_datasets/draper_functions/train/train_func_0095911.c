search_gui_guess_stats(gnet_search_t sh, const struct guess_stats *stats)
{
	search_t *search;

	search = search_gui_find(sh);
	g_return_if_fail(search != NULL);

	search->guess_cur_pool			= stats->pool;
	search->guess_cur_queried		= stats->queried;
	search->guess_cur_acks			= stats->acks;
	search->guess_cur_results		= stats->results;
	search->guess_cur_kept			= stats->kept;
	search->guess_cur_hops			= stats->hops;
	search->guess_cur_rpc_pending	= stats->rpc_pending;
	search->guess_cur_bw_query		= stats->bw_out_query;
	search->guess_cur_bw_qk			= stats->bw_out_qk;
	search->guess_cur_mode			= stats->mode;
	search->guess_cur_pool_load		= stats->pool_load;
	search->guess_cur_end_starving	= stats->end_starving;
}
