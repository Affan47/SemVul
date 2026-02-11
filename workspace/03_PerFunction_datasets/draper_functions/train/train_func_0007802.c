guess_close(void)
{
	if (NULL == db_qkdata)
		return;

	dbstore_close(db_qkdata, settings_gnet_db_dir(), db_qkdata_base);
	db_qkdata = NULL;
	cq_periodic_remove(&guess_qk_prune_ev);
	cq_periodic_remove(&guess_check_ev);
	cq_periodic_remove(&guess_sync_ev);
	cq_periodic_remove(&guess_load_ev);
	cq_periodic_remove(&guess_bw_ev);
	wq_cancel(&guess_new_host_ev);
	guess_cache_free();

	hevset_foreach(gqueries, guess_free_query, NULL);
	htable_foreach(pending, guess_rpc_free_kv, NULL);
	hevset_free_null(&gqueries);
	hikset_free_null(&gmuid);
	htable_free_null(&pending);
	aging_destroy(&guess_qk_reqs);
	aging_destroy(&guess_alien);
	hash_list_free_all(&link_cache, gnet_host_free_atom);
	hash_list_free_all(&alive_cache, gnet_host_free_atom);
	hash_list_free(&load_pending);
}
