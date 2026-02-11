hashcash_check( const char* token, int case_flag, const char* resource,
		    void **compile, char** re_err, int type, time_t now_time,
		    long validity_period, long grace_period,
		    int required_bits, time_t* token_time ) {
    time_t token_t = 0 ;
    char token_utime[ MAX_UTC+1 ] = {0};
    char token_res[ MAX_RES+1 ] = {0};
    int bits = 0, claimed_bits = 0, vers = 0;

    if ( token_time == NULL ) { token_time = &token_t; }

    if ( !hashcash_parse( token, &vers, &claimed_bits, token_utime,
			  MAX_UTC, token_res, MAX_RES, NULL, 0 ) ) {
	return HASHCASH_INVALID;
    }

    if ( vers < 0 || vers > 1 ) {
	return HASHCASH_UNSUPPORTED_VERSION;
    }

    *token_time = hashcash_from_utctimestr( token_utime, 1 );
    if ( *token_time == -1 ) {
	return HASHCASH_INVALID;
    }

    if ( !case_flag ) {
	stolower( token_res );
    }

    if ( resource &&
	 !hashcash_resource_match( type, token_res,
				   resource, compile, re_err ) ) {
	if ( *re_err != NULL ) {
	    return HASHCASH_REGEXP_ERROR;
	} else {
	    return HASHCASH_WRONG_RESOURCE;
	}
    }
    bits = hashcash_count( token );
    if ( vers == 1 ) {
	bits = ( bits < claimed_bits ) ? 0 : claimed_bits;
    }

    if ( bits < required_bits ) {
	return HASHCASH_INSUFFICIENT_BITS;
    }
    return hashcash_valid_for( *token_time, validity_period,
			       grace_period, now_time );
}
