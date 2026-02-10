hashcash_valid_for( time_t token_time, long validity_period,
			 long grace_period, time_t now_time )
{
    long expiry_time = 0 ;


    if ( validity_period == 0 )	{ return HASHCASH_VALID_FOREVER; }


    if ( token_time > now_time + grace_period ) {
	return HASHCASH_VALID_IN_FUTURE;
    }

    expiry_time = token_time + validity_period;
    if ( expiry_time + grace_period > now_time ) {

	return expiry_time + grace_period - now_time;
    }
    return HASHCASH_EXPIRED;
}
