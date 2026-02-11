keys_reclaim(struct keyinfo *ki, bool can_remove)
{
	g_assert(ki);
	g_assert(0 == ki->values);

	if (GNET_PROPERTY(dht_storage_debug) > 2)
		g_debug("DHT STORE key %s reclaimed", kuid_to_hex_string(ki->kuid));

	dbmw_delete(db_keydata, ki->kuid);
	if (can_remove)
		hikset_remove(keys, &ki->kuid);

	gnet_stats_dec_general(GNR_DHT_KEYS_HELD);
	if (ki->flags & DHT_KEY_F_CACHED)
		gnet_stats_dec_general(GNR_DHT_CACHED_KEYS_HELD);

	kuid_atom_free_null(&ki->kuid);
	ki->magic = 0;
	WFREE(ki);
}
