slapi_attr_assertion2keys_sub_sv(
    const Slapi_Attr *sattr,
    char		*initial,
    char		**any,
    char		*final,
    Slapi_Value	***ivals
)
{
	int			rc;
	Slapi_PBlock		pipb;
	struct slapdplugin	*pi = NULL;
	IFP a2k_fn = NULL;

	LDAPDebug( LDAP_DEBUG_FILTER,
	    "=> slapi_attr_assertion2keys_sub_sv\n", 0, 0, 0 );
	if ( ( sattr->a_plugin == NULL ) ) {

		slapi_attr_init_syntax((Slapi_Attr *)sattr);
	}

	if (sattr->a_mr_sub_plugin) {
		pi = sattr->a_mr_sub_plugin;
		a2k_fn = sattr->a_mr_sub_plugin->plg_mr_assertion2keys_sub;
	} else if (sattr->a_plugin) {
		pi = sattr->a_plugin;
		a2k_fn = sattr->a_plugin->plg_syntax_assertion2keys_sub;
	}
	pblock_init( &pipb );
	slapi_pblock_set( &pipb, SLAPI_PLUGIN, pi );

	rc = -1;
	*ivals = NULL;
	if ( a2k_fn != NULL ) {
		rc = (*a2k_fn)( &pipb, initial, any, final, ivals );
	}

	LDAPDebug( LDAP_DEBUG_FILTER,
	    "<= slapi_attr_assertion2keys_sub_sv %d\n", rc, 0, 0 );
	return( rc );
}
