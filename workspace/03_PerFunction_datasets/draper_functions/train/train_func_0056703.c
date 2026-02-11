retcode_send_onelevel( Operation *op, SlapReply *rs )
{
	slap_overinst	*on = (slap_overinst *)op->o_bd->bd_info;
	retcode_t	*rd = (retcode_t *)on->on_bi.bi_private;

	retcode_item_t	*rdi;

	for ( rdi = rd->rd_item; rdi != NULL; rdi = rdi->rdi_next ) {
		if ( op->o_abandon ) {
			return rs->sr_err = SLAPD_ABANDON;
		}

		rs->sr_err = test_filter( op, &rdi->rdi_e, op->ors_filter );
		if ( rs->sr_err == LDAP_COMPARE_TRUE ) {

			rs->sr_attrs = op->ors_attrs;
			rs->sr_operational_attrs = NULL;
			rs->sr_ctrls = NULL;
			rs->sr_flags = 0;
			rs->sr_err = LDAP_SUCCESS;
			rs->sr_entry = &rdi->rdi_e;

			rs->sr_err = send_search_entry( op, rs );
			rs->sr_flags = 0;
			rs->sr_entry = NULL;
			rs->sr_attrs = NULL;

			switch ( rs->sr_err ) {
			case LDAP_UNAVAILABLE:
				rs->sr_err = LDAP_OTHER;

			case LDAP_SIZELIMIT_EXCEEDED:
				goto done;
			}
		}
		rs->sr_err = LDAP_SUCCESS;
	}

done:;

	send_ldap_result( op, rs );

	return rs->sr_err;
}
