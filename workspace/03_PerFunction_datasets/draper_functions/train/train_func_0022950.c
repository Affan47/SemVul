lookup_create(const kuid_t *kuid, lookup_type_t type,
	lookup_cb_err_t error, void *arg)
{
	nlookup_t *nl;

	WALLOC0(nl);
	nl->magic = NLOOKUP_MAGIC;
	nl->kuid = kuid_get_atom(kuid);
	nl->type = type;
	nl->lid = lookup_id_create();
	nl->closest = NULL;
	nl->shortlist = patricia_create(KUID_RAW_BITSIZE);
	nl->queried = map_create_patricia(KUID_RAW_BITSIZE);
	nl->unsafe = map_create_patricia(KUID_RAW_BITSIZE);
	nl->pending = map_create_patricia(KUID_RAW_BITSIZE);
	nl->alternate = map_create_patricia(KUID_RAW_BITSIZE);
	nl->fixed = map_create_patricia(KUID_RAW_BITSIZE);
	nl->tokens = map_create_patricia(KUID_RAW_BITSIZE);
	nl->path = patricia_create(KUID_RAW_BITSIZE);
	nl->ball = patricia_create(KUID_RAW_BITSIZE);
	nl->c_class = acct_net_create();
	nl->err = error;
	nl->arg = arg;
	nl->expire_ev = cq_main_insert(NL_MAX_LIFETIME, lookup_expired, nl);
	nl->max_common_bits = KDA_C + dht_get_kball_furthest();
	tm_now_exact(&nl->start);

	htable_insert(nlookups, &nl->lid, nl);
	dht_lookup_notify(kuid, type);

	if (GNET_PROPERTY(dht_lookup_debug) > 1) {
		g_debug("DHT LOOKUP[%s] starting %s lookup for %s",
			nid_to_string(&nl->lid), lookup_type_to_string(nl),
			kuid_to_hex_string(nl->kuid));
	}

	return nl;
}
