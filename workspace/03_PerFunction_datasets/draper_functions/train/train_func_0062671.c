search_gui_guess_event(gnet_search_t sh, const struct guess_query *query)
{
	search_t *search;

	search = search_gui_find(sh);
	g_return_if_fail(search != NULL);

	if (NULL == query) {

		search->guess_bw_query += search->guess_cur_bw_query;
		search->guess_bw_qk += search->guess_cur_bw_qk;
		search->guess_results += search->guess_cur_results;
		search->guess_kept += search->guess_cur_kept;
		search->guess_elapsed = delta_time(tm_time(), search->guess_cur_start);
		search->guess_hosts = search->guess_cur_acks;
		search->guess_last_kept = search->guess_cur_kept;

		search->guess_cur_start = 0;
		search->guess_cur_pool = 0;
		search->guess_cur_queried = 0;
		search->guess_cur_acks = 0;
		search->guess_cur_results = 0;
		search->guess_cur_kept = 0;
		search->guess_cur_hops = 0;
		search->guess_cur_rpc_pending = 0;
		search->guess_cur_bw_query = 0;
		search->guess_cur_bw_qk = 0;
	} else {

		search->guess_queries++;
		search->guess_cur_start = tm_time();
		search->guess_cur_mode = query->mode;
		search->guess_cur_max_ultra = query->max_ultra;
	}
}
