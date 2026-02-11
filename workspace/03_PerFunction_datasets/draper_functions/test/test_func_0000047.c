dq_fill_next_up(dquery_t *dq, struct next_up *nv, int ncount)
{
	const GSList *sl;
	int i = 0;
	htable_t *old = NULL;

	dquery_check(dq);


	if (dq->nv != NULL) {
		int j;

		old = htable_create_any(nid_hash, nid_hash2, nid_equal);

		for (j = 0; j < dq->nv_found; j++) {
			struct next_up *nup = &dq->nv[j];
			htable_insert(old, nup->node_id, nup);
		}
	}


	GM_SLIST_FOREACH(node_all_ultranodes(), sl) {
		struct next_up *nup, *old_nup;
		struct gnutella_node *n;
		const void *knid;
		void *ttlv;
		bool found;

		if (i >= ncount)
			break;

		n = sl->data;


		if (NODE_IS_TRANSIENT(n) || !NODE_IS_WRITABLE(n))
			continue;


		if (hset_contains(dq->enqueued, NODE_ID(n)))
			continue;


		if (n->received == 0)
			continue;

		found = htable_lookup_extended(dq->queried, NODE_ID(n), &knid, &ttlv);

		if (found) {
			if (!(n->attrs & NODE_A_DQ_PROBE))
				continue;
			if (0 == (pointer_to_uint(ttlv) & DQ_TTL_PROBE))
				continue;
		}


		if (NODE_IN_TX_FLOW_CONTROL(n) || n->hops_flow == 0)
			continue;

		nup = &nv[i++];


		nup->node_id = nid_ref(NODE_ID(n));
		nup->qhv = dq->qhv;

		if (old && NULL != (old_nup = htable_lookup(old, nup->node_id))) {
			g_assert(nid_equal(NODE_ID(n), old_nup->node_id));
			nup->can_route = old_nup->can_route;
		} else
			nup->can_route = -1;
	}


	if (old) {
		g_assert(dq->nv != NULL);
		dq_free_next_up(dq);
		htable_free_null(&old);
	}

	dq->nv = nv;
	dq->nv_count = ncount;
	dq->nv_found = i;

	return i;
}
