oc_bvfind_undef( struct berval *ocname )
{
	ObjectClass	*oc = oc_bvfind( ocname );

	if ( oc ) {
		return oc;
	}

	LDAP_STAILQ_FOREACH( oc, &oc_undef_list, soc_next ) {
		int	d = oc->soc_cname.bv_len - ocname->bv_len;

		if ( d ) {
			continue;
		}

		if ( strcasecmp( oc->soc_cname.bv_val, ocname->bv_val ) == 0 ) {
			break;
		}
	}

	if ( oc ) {
		return oc;
	}

	oc = ch_malloc( sizeof( ObjectClass ) + ocname->bv_len + 1 );
	memset( oc, 0, sizeof( ObjectClass ) );

	oc->soc_cname.bv_len = ocname->bv_len;
	oc->soc_cname.bv_val = (char *)&oc[ 1 ];
	AC_MEMCPY( oc->soc_cname.bv_val, ocname->bv_val, ocname->bv_len );
	oc->soc_cname.bv_val[ oc->soc_cname.bv_len ] = '\0';


	ldap_pvt_str2upper( oc->soc_cname.bv_val );

	LDAP_STAILQ_NEXT( oc, soc_next ) = NULL;
	ldap_pvt_thread_mutex_lock( &oc_undef_mutex );
	LDAP_STAILQ_INSERT_HEAD( &oc_undef_list, oc, soc_next );
	ldap_pvt_thread_mutex_unlock( &oc_undef_mutex );

	return oc;
}
