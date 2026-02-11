tcache_prune_old(void)
{
	size_t pruned;

	if (GNET_PROPERTY(dht_tcache_debug)) {
		g_debug("DHT TCACHE pruning expired tokens (%zu)",
			dbmw_count(db_tokdata));
	}

	pruned = dbmw_foreach_remove(db_tokdata, tk_prune_old, NULL);
	gnet_stats_set_general(GNR_DHT_CACHED_TOKENS_HELD, dbmw_count(db_tokdata));

	if (GNET_PROPERTY(dht_tcache_debug)) {
		g_debug("DHT TCACHE pruned expired tokens (%zu pruned, %zu remaining)",
			pruned, dbmw_count(db_tokdata));
	}
}
