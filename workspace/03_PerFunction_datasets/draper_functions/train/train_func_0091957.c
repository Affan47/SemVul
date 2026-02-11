parse_disco (LDAP *ldap,
             const char *host_addr,
             LDAPMessage *message,
             adcli_disco **res)
{
	adcli_disco *disco = NULL;
	LDAPMessage *entry;
	struct berval **bvs;
	int usability;

	entry = ldap_first_entry (ldap, message);
	if (entry != NULL) {
		bvs = ldap_get_values_len (ldap, entry, "NetLogon");
		if (bvs != NULL) {
			if (!bvs[0])
				disco = NULL;
			else
				disco = parse_disco_data (bvs[0]);
			ldap_value_free_len (bvs);
		}
	}

	if (!disco)
		return ADCLI_DISCO_UNUSABLE;

	disco->host_addr = strdup (host_addr);
	return_val_if_fail (disco, ADCLI_DISCO_UNUSABLE);

	usability = adcli_disco_usable (disco);
	if (!insert_disco_sorted (res, disco, usability, 0))
		assert (0 && "not reached");
	return usability;
}
