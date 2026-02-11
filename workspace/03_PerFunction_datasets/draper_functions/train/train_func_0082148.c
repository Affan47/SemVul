normalize_oc_nolock( void )
{
	struct objclass	*oc;

	for ( oc = g_get_global_oc_nolock(); oc != NULL; oc = oc->oc_next ) {
	  LDAPDebug (LDAP_DEBUG_PARSE,
				 "normalize_oc: normalizing '%s'\n", oc->oc_name, 0, 0);

	  normalize_list( oc->oc_required );
	  normalize_list( oc->oc_orig_required );


	  normalize_list( oc->oc_allowed );
	  normalize_list( oc->oc_orig_allowed );
	}
}
