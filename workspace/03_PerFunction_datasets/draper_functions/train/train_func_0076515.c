meta_back_new_target(
	metatarget_t	**mtp )
{
	char			*rargv[ 3 ];
	metatarget_t		*mt;

	*mtp = NULL;

	mt = ch_calloc( sizeof( metatarget_t ), 1 );

	mt->mt_rwmap.rwm_rw = rewrite_info_init( REWRITE_MODE_USE_DEFAULT );
	if ( mt->mt_rwmap.rwm_rw == NULL ) {
		ch_free( mt );
		return -1;
	}


	rargv[ 0 ] = "rewriteContext";
	rargv[ 1 ] = "searchFilter";
	rargv[ 2 ] = NULL;
	rewrite_parse( mt->mt_rwmap.rwm_rw, "<suffix massage>", 1, 2, rargv );

	rargv[ 0 ] = "rewriteContext";
	rargv[ 1 ] = "default";
	rargv[ 2 ] = NULL;
	rewrite_parse( mt->mt_rwmap.rwm_rw, "<suffix massage>", 1, 2, rargv );

	ldap_pvt_thread_mutex_init( &mt->mt_uri_mutex );

	mt->mt_idassert_mode = LDAP_BACK_IDASSERT_LEGACY;
	mt->mt_idassert_authmethod = LDAP_AUTH_NONE;
	mt->mt_idassert_tls = SB_TLS_DEFAULT;


	mt->mt_idassert_flags = LDAP_BACK_AUTH_PRESCRIPTIVE;

	*mtp = mt;

	return 0;
}
