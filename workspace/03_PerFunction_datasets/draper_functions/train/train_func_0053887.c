dq_free_next_up(dquery_t *dq)
{
	dquery_check(dq);
	g_assert(dq->nv_count >= 0);
	g_assert(dq->nv_count >= dq->nv_found);
	g_assert((NULL == dq->nv) ^ (dq->nv_count > 0));

	if (dq->nv) {
		int i;

		for (i = 0; i < dq->nv_found; i++) {
			nid_unref(dq->nv[i].node_id);
		}
		WFREE_ARRAY(dq->nv, dq->nv_count);
		dq->nv = NULL;
		dq->nv_count = 0;
		dq->nv_found = 0;
	}
}
