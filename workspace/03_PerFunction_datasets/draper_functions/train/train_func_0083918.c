ldaptool_sasl_interact( LDAP *ld, unsigned flags, void *defaults, void *prompts ) {
	sasl_interact_t		*interact = NULL;
	ldaptoolSASLdefaults	*sasldefaults = defaults;
	int			rc;

	if (prompts == NULL) {
		return (LDAP_PARAM_ERROR);
	}

	for (interact = prompts; interact->id != SASL_CB_LIST_END; interact++) {

		if ((rc = get_default(sasldefaults, interact, flags)) != LDAP_SUCCESS) {
			return (rc);
		}


		if ( (flags == LDAP_SASL_INTERACTIVE) ||
			 ((interact->result == NULL) && (flags == LDAP_SASL_AUTOMATIC)) ) {
			if ((rc = get_new_value(interact, flags)) != LDAP_SUCCESS)
				return (rc);
		}

	}
	return (LDAP_SUCCESS);
}
