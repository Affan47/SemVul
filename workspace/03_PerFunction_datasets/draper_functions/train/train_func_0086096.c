fullNumber( const char *pnNumber, gboolean bCountryCodePrefix ) {

	if ( pnNumber == NULL || strlen( pnNumber ) <= 0 ) {
		return NULL;
	}


	pnNumber = pnNumber + callBycallPrefixLength( pnNumber );


	return formatNumber( pnNumber, bCountryCodePrefix ? requestInternationalFormat: requestNationalFormat );
}
