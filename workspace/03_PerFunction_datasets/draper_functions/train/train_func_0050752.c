ldap_back_conn_cmp( const void *c1, const void *c2 )
{
	const ldapconn_t	*lc1 = (const ldapconn_t *)c1;
	const ldapconn_t	*lc2 = (const ldapconn_t *)c2;


	return SLAP_PTRCMP( lc1->lc_conn, lc2->lc_conn );
}
