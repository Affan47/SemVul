merge_entry(
	Operation		*op,
	Entry			*e,
	int			dup,
	struct berval*		query_uuid )
{
	int		rc;
	Modifications* modlist = NULL;
	const char* 	text = NULL;
	Attribute		*attr;
	char			textbuf[SLAP_TEXT_BUFLEN];
	size_t			textlen = sizeof(textbuf);

	SlapReply sreply = {REP_RESULT};

	slap_callback cb = { NULL, slap_null_cb, NULL, NULL };

	if ( dup )
		e = entry_dup( e );
	attr = e->e_attrs;
	e->e_attrs = NULL;


	attr_merge_one( e, ad_queryId, query_uuid, NULL );


	e->e_attrs->a_next = attr;

	op->o_tag = LDAP_REQ_ADD;
	op->o_protocol = LDAP_VERSION3;
	op->o_callback = &cb;
	op->o_time = slap_get_time();
	op->o_do_not_cache = 1;

	op->ora_e = e;
	op->o_req_dn = e->e_name;
	op->o_req_ndn = e->e_nname;
	rc = op->o_bd->be_add( op, &sreply );

	if ( rc != LDAP_SUCCESS ) {
		if ( rc == LDAP_ALREADY_EXISTS ) {
			rs_reinit( &sreply, REP_RESULT );
			slap_entry2mods( e, &modlist, &text, textbuf, textlen );
			modlist->sml_op = LDAP_MOD_ADD;
			op->o_tag = LDAP_REQ_MODIFY;
			op->orm_modlist = modlist;
			op->o_managedsait = SLAP_CONTROL_CRITICAL;
			op->o_bd->be_modify( op, &sreply );
			slap_mods_free( modlist, 1 );
		} else if ( rc == LDAP_REFERRAL ||
					rc == LDAP_NO_SUCH_OBJECT ) {
			syncrepl_add_glue( op, e );
			e = NULL;
			rc = 1;
		}
		if ( e ) {
			entry_free( e );
			rc = 0;
		}
	} else {
		if ( op->ora_e == e )
			entry_free( e );
		rc = 1;
	}

	return rc;
}
