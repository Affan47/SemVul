slap_sasl_regexp_destroy( void )
{
	if ( SaslRegexp ) {
		int	n;

		for ( n = 0; n < nSaslRegexp; n++ ) {
			ch_free( SaslRegexp[ n ].sr_match );
			ch_free( SaslRegexp[ n ].sr_replace );
#ifndef SLAP_AUTH_REWRITE
			regfree( &SaslRegexp[ n ].sr_workspace );
#endif
		}

		ch_free( SaslRegexp );
	}

#ifdef SLAP_AUTH_REWRITE
	slap_sasl_rewrite_destroy();
#endif
}
