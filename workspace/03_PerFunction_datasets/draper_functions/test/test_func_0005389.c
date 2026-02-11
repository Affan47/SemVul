lookup_path_remove(nlookup_t *nl, knode_t *kn)
{
	lookup_check(nl);
	knode_check(kn);

	if (GNET_PROPERTY(dht_lookup_debug)) {
		g_debug("DHT LOOKUP[%s] removing %s from path (%u-bit common prefix)",
			nid_to_string(&nl->lid), knode_to_string(kn),
			(unsigned) kuid_common_prefix(nl->kuid, kn->id));
	}

	if (patricia_remove(nl->path, kn->id)) {
		lookup_c_class_update_count(nl, kn, -1);
		knode_refcnt_dec(kn);
	}


	if (patricia_remove(nl->ball, kn->id))
		knode_refcnt_dec(kn);

	lookup_reset_closest(nl, kn);
}
