guess_init(void)
{
	dbstore_kv_t kv = { sizeof(gnet_host_t), gnet_host_length,
		sizeof(struct qkdata),
		sizeof(struct qkdata) + sizeof(uint8) + MAX_INT_VAL(uint8) };
	dbstore_packing_t packing =
		{ serialize_qkdata, deserialize_qkdata, free_qkdata };

	if (!GNET_PROPERTY(enable_guess))
		return;

	if (db_qkdata != NULL)
		return;

	g_assert(NULL == guess_qk_prune_ev);

	db_qkdata = dbstore_open(db_qkdata_what, settings_gnet_db_dir(),
		db_qkdata_base, kv, packing, GUESS_QK_DB_CACHE_SIZE,
		gnet_host_hash, gnet_host_eq, FALSE);

	dbmw_set_map_cache(db_qkdata, GUESS_QK_MAP_CACHE_SIZE);

	guess_02_cache.hs =
		hset_create_any(gnet_host_hash, gnet_host_hash2, gnet_host_eq);

	guess_qk_prune_old();

	guess_qk_prune_ev = cq_periodic_main_add(
		GUESS_QK_PRUNE_PERIOD, guess_qk_periodic_prune, NULL);
	guess_check_ev = cq_periodic_main_add(
		GUESS_CHECK_PERIOD, guess_periodic_check, NULL);
	guess_sync_ev = cq_periodic_main_add(
		GUESS_SYNC_PERIOD, guess_periodic_sync, NULL);
	guess_load_ev = cq_periodic_main_add(
		GUESS_DBLOAD_PERIOD, guess_periodic_load, NULL);
	guess_bw_ev = cq_periodic_main_add(1000, guess_periodic_bw, NULL);

	gqueries = hevset_create_any(
		offsetof(guess_t, gid), nid_hash, nid_hash2, nid_equal);
	gmuid = hikset_create(
		offsetof(guess_t, muid), HASH_KEY_FIXED, GUID_RAW_SIZE);
	link_cache = hash_list_new(gnet_host_hash, gnet_host_eq);
	alive_cache = hash_list_new(gnet_host_hash, gnet_host_eq);
	load_pending = hash_list_new(pointer_hash, NULL);
	pending = htable_create_any(guess_rpc_key_hash, NULL, guess_rpc_key_eq);
	guess_qk_reqs = aging_make(GUESS_QK_FREQ,
		gnet_host_hash, gnet_host_eq, gnet_host_free_atom2);
	guess_alien = aging_make(GUESS_ALIEN_FREQ,
		gnet_host_hash, gnet_host_eq, gnet_host_free_atom2);

	guess_load_link_cache();
	guess_check_link_cache();
}
