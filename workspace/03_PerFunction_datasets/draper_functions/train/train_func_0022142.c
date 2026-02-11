syncprov_sendinfo(
	Operation	*op,
	SlapReply	*rs,
	int			type,
	struct berval *cookie,
	int			refreshDone,
	BerVarray	syncUUIDs,
	int			refreshDeletes )
{
	BerElementBuffer berbuf;
	BerElement *ber = (BerElement *)&berbuf;
	struct berval rspdata;

	int ret;

	ber_init2( ber, NULL, LBER_USE_DER );
	ber_set_option( ber, LBER_OPT_BER_MEMCTX, &op->o_tmpmemctx );

	if ( type ) {
		switch ( type ) {
		case LDAP_TAG_SYNC_NEW_COOKIE:
			ber_printf( ber, "tO", type, cookie );
			break;
		case LDAP_TAG_SYNC_REFRESH_DELETE:
		case LDAP_TAG_SYNC_REFRESH_PRESENT:
			ber_printf( ber, "t{", type );
			if ( cookie ) {
				ber_printf( ber, "O", cookie );
			}
			if ( refreshDone == 0 ) {
				ber_printf( ber, "b", refreshDone );
			}
			ber_printf( ber, "N}" );
			break;
		case LDAP_TAG_SYNC_ID_SET:
			ber_printf( ber, "t{", type );
			if ( cookie ) {
				ber_printf( ber, "O", cookie );
			}
			if ( refreshDeletes == 1 ) {
				ber_printf( ber, "b", refreshDeletes );
			}
			ber_printf( ber, "[W]", syncUUIDs );
			ber_printf( ber, "N}" );
			break;
		default:
			Debug( LDAP_DEBUG_TRACE,
				"syncprov_sendinfo: invalid syncinfo type (%d)\n",
				type, 0, 0 );
			return LDAP_OTHER;
		}
	}

	ret = ber_flatten2( ber, &rspdata, 0 );

	if ( ret < 0 ) {
		Debug( LDAP_DEBUG_TRACE,
			"syncprov_sendinfo: ber_flatten2 failed (%d)\n",
			ret, 0, 0 );
		send_ldap_error( op, rs, LDAP_OTHER, "internal error" );
		return LDAP_OTHER;
	}

	rs->sr_rspoid = LDAP_SYNC_INFO;
	rs->sr_rspdata = &rspdata;
	send_ldap_intermediate( op, rs );
	rs->sr_rspdata = NULL;
	ber_free_buf( ber );

	return LDAP_SUCCESS;
}
