backend_check_referrals( Operation *op, SlapReply *rs )
{
	rs->sr_err = LDAP_SUCCESS;

	if( op->o_bd->be_chk_referrals ) {
		rs->sr_err = op->o_bd->be_chk_referrals( op, rs );

		if( rs->sr_err != LDAP_SUCCESS && rs->sr_err != LDAP_REFERRAL ) {
			send_ldap_result( op, rs );
		}
	}

	return rs->sr_err;
}
