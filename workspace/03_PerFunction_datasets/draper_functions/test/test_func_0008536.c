ldap_back_conndnlc_cmp( const void *c1, const void *c2 )
{
	const ldapconn_t	*lc1 = (const ldapconn_t *)c1;
	const ldapconn_t	*lc2 = (const ldapconn_t *)c2;
	int rc;


	rc = SLAP_PTRCMP( lc1->lc_conn, lc2->lc_conn );
	if ( rc == 0 ) {
		rc = ber_bvcmp( &lc1->lc_local_ndn, &lc2->lc_local_ndn );
		if ( rc == 0 ) {
			rc = SLAP_PTRCMP( lc1, lc2 );
		}
	}

	return rc;
}
