qrt_free(struct routing_table *rt)
{
	g_assert(rt->refcnt == 0);

	atom_sha1_free_null(&rt->digest);
	HFREE_NULL(rt->arena);
	HFREE_NULL(rt->name);

	gnet_prop_set_guint32_val(PROP_QRP_MEMORY,
	  GNET_PROPERTY(qrp_memory) - (rt->compacted ? rt->slots / 8 : rt->slots));

	rt->magic = 0;
	WFREE(rt);
}
