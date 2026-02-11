syn_schema_info( Entry *e )
{
	AttributeDescription *ad_ldapSyntaxes = slap_schema.si_ad_ldapSyntaxes;
	Syntax		*syn;
	struct berval	val;
	struct berval	nval;

	LDAP_STAILQ_FOREACH(syn, &syn_list, ssyn_next ) {
		if ( ! syn->ssyn_validate ) {

			continue;
		}
		if ( syn->ssyn_flags & SLAP_SYNTAX_HIDE ) {

			continue;
		}

		if ( ldap_syntax2bv( &syn->ssyn_syn, &val ) == NULL ) {
			return -1;
		}
#if 0
		Debug( LDAP_DEBUG_TRACE, "Merging syn [%ld] %s\n",
	       (long) val.bv_len, val.bv_val, 0 );
#endif

		nval.bv_val = syn->ssyn_oid;
		nval.bv_len = strlen(syn->ssyn_oid);

		if( attr_merge_one( e, ad_ldapSyntaxes, &val, &nval ) )
		{
			return -1;
		}
		ldap_memfree( val.bv_val );
	}
	return 0;
}
