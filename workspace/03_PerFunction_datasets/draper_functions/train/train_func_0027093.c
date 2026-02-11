lookup_bucket_refresh(
	const kuid_t *kuid, size_t bits, lookup_cb_err_t done, void *arg)
{
	nlookup_t *nl;

	g_assert(kuid);
	g_assert(done);

	nl = lookup_create(kuid, LOOKUP_REFRESH, done, arg);
	nl->amount = KDA_K;
	nl->mode = LOOKUP_STRICT;
	nl->u.fn.bits = bits;
	nl->u.fn.found = 0;

	if (!lookup_load_shortlist(nl)) {
		lookup_free(nl);
		return NULL;
	}

	lookup_async_iterate(nl);
	return nl;
}
