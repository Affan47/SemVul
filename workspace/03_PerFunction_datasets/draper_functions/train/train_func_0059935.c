ldap_exop_chained_request(
		Operation	*op,
		SlapReply	*rs )
{
	Statslog( LDAP_DEBUG_STATS, "%s CHAINED REQUEST\n",
	    op->o_log_prefix, 0, 0, 0, 0 );

	rs->sr_err = backend_check_restrictions( op, rs,
			(struct berval *)&slap_EXOP_CHAINEDREQUEST );
	if ( rs->sr_err != LDAP_SUCCESS ) {
		return rs->sr_err;
	}


	rs->sr_text = "under development";
	return LDAP_UNWILLING_TO_PERFORM;
}
