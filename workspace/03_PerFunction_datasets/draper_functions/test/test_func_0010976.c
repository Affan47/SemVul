slapi_call_syntax_assertion2keys_sub_sv(
    void		*vpi,
    char		*initial,
    char		**any,
    char		*final,
    Slapi_Value	***ivals
)
{
	int			rc;
	Slapi_PBlock		pipb;
	struct slapdplugin	*pi = vpi;

	LDAPDebug( LDAP_DEBUG_FILTER,
	    "=> slapi_call_syntax_assertion2keys_sub\n", 0, 0, 0 );

	pblock_init( &pipb );
	slapi_pblock_set( &pipb, SLAPI_PLUGIN, vpi );

	rc = -1;
	*ivals = NULL;
	if ( pi->plg_syntax_assertion2keys_sub != NULL ) {
		rc = pi->plg_syntax_assertion2keys_sub( &pipb, initial, any,
		    final, ivals );
	}

	LDAPDebug( LDAP_DEBUG_FILTER,
	    "<= slapi_call_syntax_assertion2keys_sub %d\n", rc, 0, 0 );
	return( rc );
}
