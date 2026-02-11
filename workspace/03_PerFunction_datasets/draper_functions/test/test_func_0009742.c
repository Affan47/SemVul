limits_free_one(
	struct slap_limits	*lm )
{
	if ( ( lm->lm_flags & SLAP_LIMITS_MASK ) == SLAP_LIMITS_REGEX )
		regfree( &lm->lm_regex );

	if ( !BER_BVISNULL( &lm->lm_pat ) )
		ch_free( lm->lm_pat.bv_val );

	ch_free( lm );
}
