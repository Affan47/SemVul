ad_keystring(
	struct berval *bv )
{
	ber_len_t i;

	if( !AD_LEADCHAR( bv->bv_val[0] ) ) {
		return 1;
	}

	for( i=1; i<bv->bv_len; i++ ) {
		if( !AD_CHAR( bv->bv_val[i] )) {
			if ( msad_range_hack && bv->bv_val[i] == '=' )
				continue;
			return 1;
		}
	}
	return 0;
}
