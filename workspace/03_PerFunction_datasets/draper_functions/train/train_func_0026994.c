slapd_rw_apply( void *private, const char *filter, struct berval *val )
{
	slapd_map_data *sl = private;
	slap_callback cb = { NULL };
	Connection conn = {0};
	OperationBuffer opbuf;
	Operation *op;
	void *thrctx;
	SlapReply rs = {REP_RESULT};
	struct slapd_rw_info si;
	char *ptr;
	int rc;

	thrctx = ldap_pvt_thread_pool_context();
	connection_fake_init2( &conn, &opbuf, thrctx, 0 );
	op = &opbuf.ob_op;

	op->o_tag = LDAP_REQ_SEARCH;
	op->o_req_dn = op->o_req_ndn = sl->base;
	op->o_bd = select_backend( &op->o_req_ndn, 1 );
	if ( !op->o_bd ) {
		return REWRITE_ERR;
	}
	si.si_data = sl;
	BER_BVZERO( &si.si_val );
	op->ors_scope = sl->scope;
	op->ors_deref = LDAP_DEREF_NEVER;
	op->ors_slimit = 1;
	op->ors_tlimit = SLAP_NO_LIMIT;
	if ( sl->attrs[0].an_desc ) {
		op->ors_attrs = sl->attrs;
	} else {
		op->ors_attrs = slap_anlist_no_attrs;
	}
	if ( filter ) {
		rc = strlen( filter );
	} else {
		rc = 0;
	}
	rc += sl->filter.bv_len;
	ptr = op->ors_filterstr.bv_val = op->o_tmpalloc( rc + 1, op->o_tmpmemctx );
	if ( sl->filter.bv_len ) {
		ptr = lutil_strcopy( ptr, sl->filter.bv_val );
	} else {
		*ptr = '\0';
	}
	if ( filter ) {
		strcpy( ptr, filter );
	}
	op->ors_filter = str2filter_x( op, op->ors_filterstr.bv_val );
	if ( !op->ors_filter ) {
		op->o_tmpfree( op->ors_filterstr.bv_val, op->o_tmpmemctx );
		return REWRITE_ERR;
	}

	op->ors_attrsonly = 0;
	op->o_dn = op->o_bd->be_rootdn;
	op->o_ndn = op->o_bd->be_rootndn;
	op->o_do_not_cache = 1;

	cb.sc_response = slapd_rw_cb;
	cb.sc_private = &si;
	op->o_callback = &cb;

	rc = op->o_bd->be_search( op, &rs );
	if ( rc == LDAP_SUCCESS && !BER_BVISNULL( &si.si_val )) {
		*val = si.si_val;
		rc = REWRITE_SUCCESS;
	} else {
		if ( !BER_BVISNULL( &si.si_val )) {
			ch_free( si.si_val.bv_val );
		}
		rc = REWRITE_ERR;
	}
	filter_free_x( op, op->ors_filter, 1 );
	op->o_tmpfree( op->ors_filterstr.bv_val, op->o_tmpmemctx );
	return rc;
}
