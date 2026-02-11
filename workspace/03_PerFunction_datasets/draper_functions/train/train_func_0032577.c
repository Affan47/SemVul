free_ue_cache(snmp_ue_assoc_t **cache)
{
	static snmp_ue_assoc_t *a, *nxt;

	for (a = *cache; a; a = nxt) {
		nxt = a->next;
		snmp_users_free_cb(a);
		g_free(a);
	}

	*cache = NULL;
}
