syn_unparse( BerVarray *res, Syntax *start, Syntax *end, int sys )
{
	Syntax *syn;
	int i, num;
	struct berval bv, *bva = NULL, idx;
	char ibuf[32];

	if ( !start )
		start = LDAP_STAILQ_FIRST( &syn_list );


	i = 0;
	for ( syn = start; syn; syn = LDAP_STAILQ_NEXT( syn, ssyn_next ) ) {
		if ( sys && !( syn->ssyn_flags & SLAP_SYNTAX_HARDCODE ) ) break;
		i++;
		if ( syn == end ) break;
	}
	if ( !i ) return;

	num = i;
	bva = ch_malloc( (num+1) * sizeof(struct berval) );
	BER_BVZERO( bva );
	idx.bv_val = ibuf;
	if ( sys ) {
		idx.bv_len = 0;
		ibuf[0] = '\0';
	}
	i = 0;
	for ( syn = start; syn; syn = LDAP_STAILQ_NEXT( syn, ssyn_next ) ) {
		if ( sys && !( syn->ssyn_flags & SLAP_SYNTAX_HARDCODE ) ) break;
		if ( ldap_syntax2bv( &syn->ssyn_syn, &bv ) == NULL ) {
			ber_bvarray_free( bva );
		}
		if ( !sys ) {
			idx.bv_len = sprintf(idx.bv_val, "{%d}", i);
		}
		bva[i].bv_len = idx.bv_len + bv.bv_len;
		bva[i].bv_val = ch_malloc( bva[i].bv_len + 1 );
		strcpy( bva[i].bv_val, ibuf );
		strcpy( bva[i].bv_val + idx.bv_len, bv.bv_val );
		i++;
		bva[i].bv_val = NULL;
		ldap_memfree( bv.bv_val );
		if ( syn == end ) break;
	}
	*res = bva;
}
