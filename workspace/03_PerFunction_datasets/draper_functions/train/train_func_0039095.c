ldap_back_db_init( Backend *be, ConfigReply *cr )
{
	ldapinfo_t	*li;
	int		rc;
	unsigned	i;

	li = (ldapinfo_t *)ch_calloc( 1, sizeof( ldapinfo_t ) );
	if ( li == NULL ) {
 		return -1;
 	}

	li->li_rebind_f = ldap_back_default_rebind;
	li->li_urllist_f = ldap_back_default_urllist;
	li->li_urllist_p = li;
	ldap_pvt_thread_mutex_init( &li->li_uri_mutex );

	BER_BVZERO( &li->li_acl_authcID );
	BER_BVZERO( &li->li_acl_authcDN );
	BER_BVZERO( &li->li_acl_passwd );

	li->li_acl_authmethod = LDAP_AUTH_NONE;
	BER_BVZERO( &li->li_acl_sasl_mech );
	li->li_acl.sb_tls = SB_TLS_DEFAULT;

	li->li_idassert_mode = LDAP_BACK_IDASSERT_LEGACY;

	BER_BVZERO( &li->li_idassert_authcID );
	BER_BVZERO( &li->li_idassert_authcDN );
	BER_BVZERO( &li->li_idassert_passwd );

	BER_BVZERO( &li->li_idassert_authzID );

	li->li_idassert_authmethod = LDAP_AUTH_NONE;
	BER_BVZERO( &li->li_idassert_sasl_mech );
	li->li_idassert_tls = SB_TLS_DEFAULT;


	li->li_idassert_flags = LDAP_BACK_AUTH_PRESCRIPTIVE;

	li->li_idassert_authz = NULL;


	li->li_flags = LDAP_BACK_F_CHASE_REFERRALS;


	li->li_version = LDAP_VERSION3;

	ldap_pvt_thread_mutex_init( &li->li_conninfo.lai_mutex );

	for ( i = LDAP_BACK_PCONN_FIRST; i < LDAP_BACK_PCONN_LAST; i++ ) {
		li->li_conn_priv[ i ].lic_num = 0;
		LDAP_TAILQ_INIT( &li->li_conn_priv[ i ].lic_priv );
	}
	li->li_conn_priv_max = LDAP_BACK_CONN_PRIV_DEFAULT;

	be->be_private = li;
	SLAP_DBFLAGS( be ) |= SLAP_DBFLAG_NOLASTMOD;

	be->be_cf_ocs = be->bd_info->bi_cf_ocs;

	rc = ldap_back_monitor_db_init( be );
	if ( rc != 0 ) {

		rc = 0;
	}

	return rc;
}
