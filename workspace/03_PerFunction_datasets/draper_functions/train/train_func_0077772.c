meta_back_proxy_authz_bind(
	metaconn_t *mc,
	int candidate,
	Operation *op,
	SlapReply *rs,
	ldap_back_send_t sendok,
	int dolock )
{
	metainfo_t		*mi = (metainfo_t *)op->o_bd->be_private;
	metatarget_t		*mt = mi->mi_targets[ candidate ];
	metasingleconn_t	*msc = &mc->mc_conns[ candidate ];
	struct berval		binddn = BER_BVC( "" ),
				cred = BER_BVC( "" );
	int			method = LDAP_AUTH_NONE,
				rc;

	rc = meta_back_proxy_authz_cred( mc, candidate, op, rs, sendok, &binddn, &cred, &method );
	if ( rc == LDAP_SUCCESS && !LDAP_BACK_CONN_ISBOUND( msc ) ) {
		int	msgid;

		switch ( method ) {
		case LDAP_AUTH_NONE:
		case LDAP_AUTH_SIMPLE:
			for (;;) {
				rs->sr_err = ldap_sasl_bind( msc->msc_ld,
					binddn.bv_val, LDAP_SASL_SIMPLE,
					&cred, NULL, NULL, &msgid );
				if ( rs->sr_err != LDAP_X_CONNECTING ) {
					break;
				}
				ldap_pvt_thread_yield();
			}
			rc = meta_back_bind_op_result( op, rs, mc, candidate, msgid, sendok, dolock );
			if ( rc == LDAP_SUCCESS ) {


				LDAP_BACK_CONN_ISBOUND_SET( msc );
				ber_bvreplace( &msc->msc_bound_ndn, &binddn );

				if ( META_BACK_TGT_SAVECRED( mt ) ) {
					if ( !BER_BVISNULL( &msc->msc_cred ) ) {
						memset( msc->msc_cred.bv_val, 0,
							msc->msc_cred.bv_len );
					}
					ber_bvreplace( &msc->msc_cred, &cred );
					ldap_set_rebind_proc( msc->msc_ld, mt->mt_rebind_f, msc );
				}
			}
			break;

		default:
			assert( 0 );
			break;
		}
	}

	return LDAP_BACK_CONN_ISBOUND( msc );
}
