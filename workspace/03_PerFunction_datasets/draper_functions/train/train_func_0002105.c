xmms_collection_foreach_in_namespace (xmms_coll_dag_t *dag, guint nsid, GHFunc f, void *udata)
{
	gint i;

	if (nsid == XMMS_COLLECTION_NSID_ALL) {
		for (i = 0; i < XMMS_COLLECTION_NUM_NAMESPACES; ++i) {
			g_hash_table_foreach (dag->collrefs[i], f, udata);
		}
	} else if (nsid != XMMS_COLLECTION_NSID_INVALID) {
		g_hash_table_foreach (dag->collrefs[nsid], f, udata);
	}
}
