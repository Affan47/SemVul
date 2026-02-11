acl_match_set (
	struct berval *subj,
	Operation *op,
	Entry *e,
	struct berval *default_set_attribute )
{
	struct berval	set = BER_BVNULL;
	int		rc = 0;
	AclSetCookie	cookie;

	if ( default_set_attribute == NULL ) {
		set = *subj;

	} else {
		struct berval		subjdn, ndn = BER_BVNULL;
		struct berval		setat;
		BerVarray		bvals = NULL;
		const char		*text;
		AttributeDescription	*desc = NULL;


		if ( acl_get_part( subj, 0, '/', &subjdn ) < 0 ) {
			return 0;
		}

		if ( acl_get_part( subj, 1, '/', &setat ) < 0 ) {
			setat = *default_set_attribute;
		}


		if ( slap_bv2ad( &setat, &desc, &text ) == LDAP_SUCCESS ) {
			if ( dnNormalize( 0, NULL, NULL, &subjdn, &ndn, op->o_tmpmemctx ) == LDAP_SUCCESS )
			{
				backend_attribute( op, e, &ndn, desc, &bvals, ACL_NONE );
				if ( bvals != NULL && !BER_BVISNULL( &bvals[0] ) ) {
					int	i;

					set = bvals[0];
					BER_BVZERO( &bvals[0] );
					for ( i = 1; !BER_BVISNULL( &bvals[i] ); i++ )
						 ;
					bvals[0].bv_val = bvals[i-1].bv_val;
					BER_BVZERO( &bvals[i-1] );
				}
				ber_bvarray_free_x( bvals, op->o_tmpmemctx );
				slap_sl_free( ndn.bv_val, op->o_tmpmemctx );
			}
		}
	}

	if ( !BER_BVISNULL( &set ) ) {
		cookie.asc_op = op;
		cookie.asc_e = e;
		rc = ( slap_set_filter(
			acl_set_gather,
			(SetCookie *)&cookie, &set,
			&op->o_ndn, &e->e_nname, NULL ) > 0 );
		if ( set.bv_val != subj->bv_val ) {
			slap_sl_free( set.bv_val, op->o_tmpmemctx );
		}
	}

	return(rc);
}
