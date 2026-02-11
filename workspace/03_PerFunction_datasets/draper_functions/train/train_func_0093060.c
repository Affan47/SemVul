ppolicy_compare(
	Operation *op,
	SlapReply *rs )
{
	slap_overinst *on = (slap_overinst *)op->o_bd->bd_info;

	if ( ppolicy_restrict( op, rs ) != SLAP_CB_CONTINUE )
		return rs->sr_err;


	if ( op->o_ctrlflag[ppolicy_cid] &&
		op->orc_ava->aa_desc == slap_schema.si_ad_userPassword ) {
		Entry *e;
		int rc;
		ppbind *ppb;
		slap_callback *cb;

		op->o_bd->bd_info = (BackendInfo *)on->on_info;
		rc = be_entry_get_rw( op, &op->o_req_ndn, NULL, NULL, 0, &e );

		if ( rc != LDAP_SUCCESS ) {
			return SLAP_CB_CONTINUE;
		}

		cb = op->o_tmpcalloc( sizeof(ppbind)+sizeof(slap_callback),
			1, op->o_tmpmemctx );
		ppb = (ppbind *)(cb+1);
		ppb->on = on;
		ppb->pErr = PP_noError;
		ppb->send_ctrl = 1;

		ppb->set_restrict = 0;


		cb->sc_response = ppolicy_compare_response;
		cb->sc_next = op->o_callback->sc_next;
		cb->sc_private = ppb;
		op->o_callback->sc_next = cb;

		op->o_bd->bd_info = (BackendInfo *)on;
		ppolicy_get( op, e, &ppb->pp );

		rc = account_locked( op, e, &ppb->pp, &ppb->mod );

		op->o_bd->bd_info = (BackendInfo *)on->on_info;
		be_entry_release_r( op, e );

		if ( rc ) {
			ppb->pErr = PP_accountLocked;
			send_ldap_error( op, rs, LDAP_COMPARE_FALSE, NULL );
			return rs->sr_err;
		}
	}
	return SLAP_CB_CONTINUE;
}
