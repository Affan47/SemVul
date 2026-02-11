slap_sort_csn_sids( BerVarray csns, int *sids, int numcsns, void *memctx )
{
	Attribute a;
	const char *text;
	int i, rc;

	a.a_desc = (AttributeDescription *)&sidsort_ad;
	a.a_nvals = slap_sl_malloc( numcsns * sizeof(struct berval), memctx );
	for ( i=0; i<numcsns; i++ ) {
		a.a_nvals[i].bv_len = sids[i];
		a.a_nvals[i].bv_val = NULL;
	}
	a.a_vals = csns;
	a.a_numvals = numcsns;
	a.a_flags = 0;
	rc = slap_sort_vals( (Modifications *)&a, &text, &i, memctx );
	for ( i=0; i<numcsns; i++ )
		sids[i] = a.a_nvals[i].bv_len;
	slap_sl_free( a.a_nvals, memctx );
	return rc;
}
