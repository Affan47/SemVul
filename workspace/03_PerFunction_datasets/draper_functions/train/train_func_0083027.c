slap_parse_modlist(
	Operation *op,
	SlapReply *rs,
	BerElement *ber,
	req_modify_s *ms )
{
	ber_tag_t	tag;
	ber_len_t	len;
	char		*last;
	Modifications	**modtail = &ms->rs_mods.rs_modlist;

	ms->rs_mods.rs_modlist = NULL;
	ms->rs_increment = 0;

	rs->sr_err = LDAP_SUCCESS;


	for ( tag = ber_first_element( ber, &len, &last );
		tag != LBER_DEFAULT;
		tag = ber_next_element( ber, &len, last ) )
	{
		ber_int_t mop;
		Modifications tmp, *mod;

		tmp.sml_nvalues = NULL;

		if ( ber_scanf( ber, "{e{m[W]}}", &mop,
		    &tmp.sml_type, &tmp.sml_values ) == LBER_ERROR )
		{
			rs->sr_text = "decoding modlist error";
			rs->sr_err = LDAP_PROTOCOL_ERROR;
			goto done;
		}

		mod = (Modifications *) ch_malloc( sizeof(Modifications) );
		mod->sml_op = mop;
		mod->sml_flags = 0;
		mod->sml_type = tmp.sml_type;
		mod->sml_values = tmp.sml_values;
		mod->sml_nvalues = NULL;
		mod->sml_desc = NULL;
		mod->sml_next = NULL;
		*modtail = mod;

		switch( mop ) {
		case LDAP_MOD_ADD:
			if ( mod->sml_values == NULL ) {
				rs->sr_text = "modify/add operation requires values";
				rs->sr_err = LDAP_PROTOCOL_ERROR;
				goto done;
			}


		case LDAP_MOD_DELETE:
		case LDAP_MOD_REPLACE:
			break;

		case LDAP_MOD_INCREMENT:
			if( op->o_protocol >= LDAP_VERSION3 ) {
				ms->rs_increment++;
				if ( mod->sml_values == NULL ) {
					rs->sr_text = "modify/increment operation requires value";
					rs->sr_err = LDAP_PROTOCOL_ERROR;
					goto done;
				}

				if ( !BER_BVISNULL( &mod->sml_values[ 1 ] ) ) {
					rs->sr_text = "modify/increment operation requires single value";
					rs->sr_err = LDAP_PROTOCOL_ERROR;
					goto done;
				}

				break;
			}


		default:
			rs->sr_text = "unrecognized modify operation";
			rs->sr_err = LDAP_PROTOCOL_ERROR;
			goto done;
		}

		modtail = &mod->sml_next;
	}
	*modtail = NULL;

done:
	if ( rs->sr_err != LDAP_SUCCESS ) {
		slap_mods_free( ms->rs_mods.rs_modlist, 1 );
		ms->rs_mods.rs_modlist = NULL;
		ms->rs_increment = 0;
	}

	return rs->sr_err;
}
