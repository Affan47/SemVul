translucent_exop(Operation *op, SlapReply *rs) {
	slap_overinst *on = (slap_overinst *) op->o_bd->bd_info;
	translucent_info *ov = on->on_bi.bi_private;
	const struct berval bv_exop_pwmod = BER_BVC(LDAP_EXOP_MODIFY_PASSWD);

	Debug(LDAP_DEBUG_TRACE, "==> translucent_exop: %s\n",
		op->o_req_dn.bv_val, 0, 0);

	if(ov->defer_db_open) {
		send_ldap_error(op, rs, LDAP_UNAVAILABLE,
			"remote DB not available");
		return(rs->sr_err);
	}

	if ( bvmatch( &bv_exop_pwmod, &op->ore_reqoid ) ) {
		return translucent_pwmod( op, rs );
	}

	return SLAP_CB_CONTINUE;
}
