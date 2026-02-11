do_extended(
    Operation	*op,
    SlapReply	*rs
)
{
	struct berval reqdata = {0, NULL};
	ber_len_t len;

	Debug( LDAP_DEBUG_TRACE, "%s do_extended\n",
		op->o_log_prefix, 0, 0 );

	if( op->o_protocol < LDAP_VERSION3 ) {
		Debug( LDAP_DEBUG_ANY, "%s do_extended: protocol version (%d) too low\n",
			op->o_log_prefix, op->o_protocol, 0 );
		send_ldap_discon( op, rs, LDAP_PROTOCOL_ERROR, "requires LDAPv3" );
		rs->sr_err = SLAPD_DISCONNECT;
		goto done;
	}

	if ( ber_scanf( op->o_ber, "{m" , &op->ore_reqoid ) == LBER_ERROR ) {
		Debug( LDAP_DEBUG_ANY, "%s do_extended: ber_scanf failed\n",
			op->o_log_prefix, 0, 0 );
		send_ldap_discon( op, rs, LDAP_PROTOCOL_ERROR, "decoding error" );
		rs->sr_err = SLAPD_DISCONNECT;
		goto done;
	}

	if( ber_peek_tag( op->o_ber, &len ) == LDAP_TAG_EXOP_REQ_VALUE ) {
		if( ber_scanf( op->o_ber, "m", &reqdata ) == LBER_ERROR ) {
			Debug( LDAP_DEBUG_ANY, "%s do_extended: ber_scanf failed\n",
				op->o_log_prefix, 0, 0 );
			send_ldap_discon( op, rs, LDAP_PROTOCOL_ERROR, "decoding error" );
			rs->sr_err = SLAPD_DISCONNECT;
			goto done;
		}
	}

	if( get_ctrls( op, rs, 1 ) != LDAP_SUCCESS ) {
		Debug( LDAP_DEBUG_ANY, "%s do_extended: get_ctrls failed\n",
			op->o_log_prefix, 0, 0 );
		return rs->sr_err;
	}

	Statslog( LDAP_DEBUG_STATS, "%s EXT oid=%s\n",
	    op->o_log_prefix, op->ore_reqoid.bv_val, 0, 0, 0 );


	if( get_manageDSAit( op ) == SLAP_CONTROL_CRITICAL ) {
		send_ldap_error( op, rs,
			LDAP_UNAVAILABLE_CRITICAL_EXTENSION,
			"manageDSAit control inappropriate" );
		goto done;
	}


	if ( reqdata.bv_val ) {
		op->ore_reqdata = &reqdata;
	}

	op->o_bd = frontendDB;
	rs->sr_err = frontendDB->be_extended( op, rs );


	if ( !BER_BVISNULL( &op->o_req_ndn ) ) {
		if ( !BER_BVISNULL( &op->o_req_dn )
			&& op->o_req_ndn.bv_val != op->o_req_dn.bv_val )
		{
			op->o_tmpfree( op->o_req_dn.bv_val, op->o_tmpmemctx );
		}
		op->o_tmpfree( op->o_req_ndn.bv_val, op->o_tmpmemctx );
		BER_BVZERO( &op->o_req_dn );
		BER_BVZERO( &op->o_req_ndn );
	}

done:
	return rs->sr_err;
}
