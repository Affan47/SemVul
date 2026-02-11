mr_destroy( void )
{
	MatchingRule *m;

	avl_free(mr_index, ldap_memfree);
	while( !LDAP_SLIST_EMPTY(&mr_list) ) {
		m = LDAP_SLIST_FIRST(&mr_list);
		LDAP_SLIST_REMOVE_HEAD(&mr_list, smr_next);
		ch_free( m->smr_str.bv_val );
		ch_free( m->smr_compat_syntaxes );
		ldap_matchingrule_free((LDAPMatchingRule *)m);
	}
}
