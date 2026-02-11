slap_sasl_regexp_unparse( BerVarray *out )
{
	int i;
	BerVarray bva = NULL;
	char ibuf[32], *ptr;
	struct berval idx;

	if ( !nSaslRegexp ) return;

	idx.bv_val = ibuf;
	bva = ch_malloc( (nSaslRegexp+1) * sizeof(struct berval) );
	BER_BVZERO(bva+nSaslRegexp);
	for ( i=0; i<nSaslRegexp; i++ ) {
		idx.bv_len = sprintf( idx.bv_val, "{%d}", i);
		bva[i].bv_len = idx.bv_len + strlen( SaslRegexp[i].sr_match ) +
			strlen( SaslRegexp[i].sr_replace ) + 5;
		bva[i].bv_val = ch_malloc( bva[i].bv_len+1 );
		ptr = lutil_strcopy( bva[i].bv_val, ibuf );
		*ptr++ = '"';
		ptr = lutil_strcopy( ptr, SaslRegexp[i].sr_match );
		ptr = lutil_strcopy( ptr, "\" \"" );
		ptr = lutil_strcopy( ptr, SaslRegexp[i].sr_replace );
		*ptr++ = '"';
		*ptr = '\0';
	}
	*out = bva;
}
