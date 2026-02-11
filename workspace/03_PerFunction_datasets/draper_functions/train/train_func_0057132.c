lookup_value_free(nlookup_t *nl, bool free_vvec)
{
	GSList *sl;
	struct fvalue *fv;
	int i;

	lookup_value_check(nl);

	fv = lookup_fv(nl);

	if (free_vvec) {
		for (i = 0; i < fv->vcnt; i++)
			dht_value_free(fv->vvec[i], TRUE);

		WFREE_ARRAY(fv->vvec, fv->vsize);
	}

	GM_SLIST_FOREACH(fv->seckeys, sl) {
		struct seckeys *sk = sl->data;

		g_assert(sk->skeys);
		g_assert(sk->scnt > 0);

		seckeys_free(sk);
	}

	gm_slist_free_null(&fv->seckeys);
	map_foreach(fv->seen, lookup_value_seen_free_kv, NULL);
	map_destroy(fv->seen);
	map_destroy(fv->values);
	cq_cancel(&fv->delay_ev);
	WFREE(fv);

	nl->u.fv.fv = NULL;
}
