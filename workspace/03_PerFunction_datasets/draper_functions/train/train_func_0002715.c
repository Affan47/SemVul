ldap_chain_parse_ctrl(
	Operation	*op,
	SlapReply	*rs,
	LDAPControl	*ctrl )
{
	ber_tag_t	tag;
	BerElement	*ber;
	ber_int_t	mode,
			behavior;

	if ( get_chaining( op ) != SLAP_CONTROL_NONE ) {
		rs->sr_text = "Chaining behavior control specified multiple times";
		return LDAP_PROTOCOL_ERROR;
	}

	if ( op->o_pagedresults != SLAP_CONTROL_NONE ) {
		rs->sr_text = "Chaining behavior control specified with pagedResults control";
		return LDAP_PROTOCOL_ERROR;
	}

	if ( BER_BVISEMPTY( &ctrl->ldctl_value ) ) {
		mode = (SLAP_CH_RESOLVE_DEFAULT|SLAP_CH_CONTINUATION_DEFAULT);

	} else {
		ber_len_t	len;


		ber = ber_init( &ctrl->ldctl_value );
		if( ber == NULL ) {
			rs->sr_text = "internal error";
			return LDAP_OTHER;
		}

		tag = ber_scanf( ber, "{e" , &behavior );


		if ( tag != LBER_ENUMERATED ) {
			rs->sr_text = "Chaining behavior control: resolveBehavior decoding error";
			return LDAP_PROTOCOL_ERROR;
		}

		switch ( behavior ) {
		case LDAP_CHAINING_PREFERRED:
			mode = SLAP_CH_RESOLVE_CHAINING_PREFERRED;
			break;

		case LDAP_CHAINING_REQUIRED:
			mode = SLAP_CH_RESOLVE_CHAINING_REQUIRED;
			break;

		case LDAP_REFERRALS_PREFERRED:
			mode = SLAP_CH_RESOLVE_REFERRALS_PREFERRED;
			break;

		case LDAP_REFERRALS_REQUIRED:
			mode = SLAP_CH_RESOLVE_REFERRALS_REQUIRED;
			break;

		default:
			rs->sr_text = "Chaining behavior control: unknown resolveBehavior";
			return LDAP_PROTOCOL_ERROR;
		}

		tag = ber_peek_tag( ber, &len );
		if ( tag == LBER_ENUMERATED ) {
			tag = ber_scanf( ber, "e", &behavior );
			if ( tag == LBER_ERROR ) {
				rs->sr_text = "Chaining behavior control: continuationBehavior decoding error";
				return LDAP_PROTOCOL_ERROR;
			}
		}

		if ( tag == LBER_DEFAULT ) {
			mode |= SLAP_CH_CONTINUATION_DEFAULT;

		} else {
			switch ( behavior ) {
			case LDAP_CHAINING_PREFERRED:
				mode |= SLAP_CH_CONTINUATION_CHAINING_PREFERRED;
				break;

			case LDAP_CHAINING_REQUIRED:
				mode |= SLAP_CH_CONTINUATION_CHAINING_REQUIRED;
				break;

			case LDAP_REFERRALS_PREFERRED:
				mode |= SLAP_CH_CONTINUATION_REFERRALS_PREFERRED;
				break;

			case LDAP_REFERRALS_REQUIRED:
				mode |= SLAP_CH_CONTINUATION_REFERRALS_REQUIRED;
				break;

			default:
				rs->sr_text = "Chaining behavior control: unknown continuationBehavior";
				return LDAP_PROTOCOL_ERROR;
			}
		}

		if ( ( ber_scanf( ber,  "}") ) == LBER_ERROR ) {
			rs->sr_text = "Chaining behavior control: decoding error";
			return LDAP_PROTOCOL_ERROR;
		}

		(void) ber_free( ber, 1 );
	}

	op->o_chaining = mode | ( ctrl->ldctl_iscritical
			? SLAP_CONTROL_CRITICAL
			: SLAP_CONTROL_NONCRITICAL );

	return LDAP_SUCCESS;
}
