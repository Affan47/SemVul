lookup_shortlist_add(nlookup_t *nl, const knode_t *kn)
{
	lookup_check(nl);
	knode_check(kn);
	g_assert(!map_contains(nl->queried, kn->id));
	g_assert(!map_contains(nl->pending, kn->id));
	g_assert(!patricia_contains(nl->shortlist, kn->id));
	g_assert(!patricia_contains(nl->ball, kn->id));

	patricia_insert(nl->shortlist, kn->id, knode_refcnt_inc(kn));


	patricia_insert(nl->ball, kn->id, knode_refcnt_inc(kn));
}
