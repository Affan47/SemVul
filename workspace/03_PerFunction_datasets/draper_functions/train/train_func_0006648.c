autogroup_db_open(
	BackendDB	*be,
	ConfigReply	*cr )
{
	slap_overinst			*on = (slap_overinst *) be->bd_info;
	autogroup_info_t		*agi = on->on_bi.bi_private;
	autogroup_def_t		*agd;
	autogroup_sc_t		ags;
	Operation		*op;
	slap_callback		cb = { 0 };

	void				*thrctx = ldap_pvt_thread_pool_context();
	Connection			conn = { 0 };
	OperationBuffer 	opbuf;

	Debug( LDAP_DEBUG_TRACE, "==> autogroup_db_open\n", 0, 0, 0);

	if ( agi == NULL || !( slapMode & SLAP_SERVER_MODE )) {
		return 0;
	}

	connection_fake_init( &conn, &opbuf, thrctx );
	op = &opbuf.ob_op;

	op->ors_attrsonly = 0;
	op->o_tag = LDAP_REQ_SEARCH;
	op->o_dn = be->be_rootdn;
	op->o_ndn = be->be_rootndn;

	op->o_req_dn = be->be_suffix[0];
	op->o_req_ndn = be->be_nsuffix[0];

	op->ors_scope = LDAP_SCOPE_SUBTREE;
	op->ors_deref = LDAP_DEREF_NEVER;
	op->ors_limit = NULL;
	op->ors_tlimit = SLAP_NO_LIMIT;
	op->ors_slimit = SLAP_NO_LIMIT;
	op->ors_attrs =  slap_anlist_no_attrs;

	op->o_bd = be;
	op->o_bd->bd_info = (BackendInfo *)on->on_info;

	ags.ags_info = agi;
	cb.sc_private = &ags;
	cb.sc_response = autogroup_group_add_cb;
	cb.sc_cleanup = NULL;
	cb.sc_next = NULL;

	op->o_callback = &cb;

	for (agd = agi->agi_def ; agd ; agd = agd->agd_next) {
		SlapReply	rs = { REP_RESULT };

		autogroup_build_def_filter(agd, op);

		ags.ags_def = agd;

		op->o_bd->be_search( op, &rs );

		filter_free_x( op, op->ors_filter, 1 );
		op->o_tmpfree( op->ors_filterstr.bv_val, op->o_tmpmemctx );
	}

	if( ! agi->agi_memberof_ad ){
		int			rc;
		const char		*text = NULL;

		rc = slap_str2ad( SLAPD_MEMBEROF_ATTR, &agi->agi_memberof_ad, &text );
		if ( rc != LDAP_SUCCESS ) {
			Debug( LDAP_DEBUG_ANY, "autogroup_db_open: "
			"unable to find attribute=\"%s\": %s (%d)\n",
			SLAPD_MEMBEROF_ATTR, text, rc );
			return rc;
		}
	}

	return 0;
}
