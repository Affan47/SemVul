ldap_back_db_open( BackendDB *be, ConfigReply *cr )
{
	ldapinfo_t	*li = (ldapinfo_t *)be->be_private;

	slap_bindconf	sb = { BER_BVNULL };
	int		rc = 0;

	Debug( LDAP_DEBUG_TRACE,
		"ldap_back_db_open: URI=%s\n",
		li->li_uri != NULL ? li->li_uri : "", 0, 0 );


	switch ( li->li_idassert_mode ) {
	case LDAP_BACK_IDASSERT_LEGACY:
	case LDAP_BACK_IDASSERT_SELF:


		li->li_idassert_flags &= ~LDAP_BACK_AUTH_NATIVE_AUTHZ;
		break;

	default:
		break;
	}

	ber_str2bv( li->li_uri, 0, 0, &sb.sb_uri );
	sb.sb_version = li->li_version;
	sb.sb_method = LDAP_AUTH_SIMPLE;
	BER_BVSTR( &sb.sb_binddn, "" );

	if ( LDAP_BACK_T_F_DISCOVER( li ) && !LDAP_BACK_T_F( li ) ) {
		rc = slap_discover_feature( &sb,
				slap_schema.si_ad_supportedFeatures->ad_cname.bv_val,
				LDAP_FEATURE_ABSOLUTE_FILTERS );
		if ( rc == LDAP_COMPARE_TRUE ) {
			li->li_flags |= LDAP_BACK_F_T_F;
		}
	}

	if ( LDAP_BACK_CANCEL_DISCOVER( li ) && !LDAP_BACK_CANCEL( li ) ) {
		rc = slap_discover_feature( &sb,
				slap_schema.si_ad_supportedExtension->ad_cname.bv_val,
				LDAP_EXOP_CANCEL );
		if ( rc == LDAP_COMPARE_TRUE ) {
			li->li_flags |= LDAP_BACK_F_CANCEL_EXOP;
		}
	}


	rc = ldap_back_monitor_db_open( be );
	if ( rc != 0 ) {

		rc = 0;
	}

	li->li_flags |= LDAP_BACK_F_ISOPEN;

	return rc;
}
