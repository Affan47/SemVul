mru_destroy( void )
{
	MatchingRuleUse *m;

	while( !LDAP_SLIST_EMPTY(&mru_list) ) {
		m = LDAP_SLIST_FIRST(&mru_list);
		LDAP_SLIST_REMOVE_HEAD(&mru_list, smru_next);

		if ( m->smru_str.bv_val ) {
			ch_free( m->smru_str.bv_val );
			m->smru_str.bv_val = NULL;
		}

		m->smru_oid = NULL;
		m->smru_names = NULL;
		m->smru_desc = NULL;


		ldap_matchingruleuse_free((LDAPMatchingRuleUse *)m);
	}
}
