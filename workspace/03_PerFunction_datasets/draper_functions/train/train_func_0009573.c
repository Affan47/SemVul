monitor_search2ndn_cb( Operation *op, SlapReply *rs )
{
	if ( rs->sr_type == REP_SEARCH ) {
		struct berval	*ndn = op->o_callback->sc_private;

		if ( !BER_BVISNULL( ndn ) ) {
			rs->sr_err = LDAP_SIZELIMIT_EXCEEDED;
			ch_free( ndn->bv_val );
			BER_BVZERO( ndn );
			return rs->sr_err;
		}

		ber_dupbv( ndn, &rs->sr_entry->e_nname );
	}

	return 0;
}
