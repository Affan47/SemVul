connect_to_directory (adcli_conn *conn)
{
	adcli_result res = ADCLI_ERR_UNEXPECTED;
	adcli_disco *disco;
	int had_any = 0;

	if (conn->ldap)
		return ADCLI_SUCCESS;

	disco_dance_if_necessary (conn);

	if (!conn->domain_disco)
		conn->domain_disco = desperate_for_disco (conn);

	for (disco = conn->domain_disco; disco != NULL; disco = disco->next) {
		if (!adcli_disco_usable (disco))
			continue;
		res = connect_and_lookup_naming (conn, disco);
		if (res == ADCLI_SUCCESS || res == ADCLI_ERR_UNEXPECTED)
			return res;
		had_any = 1;
	}

	if (!had_any) {
		_adcli_err ("Couldn't find usable domain controller to connect to");
		return ADCLI_ERR_CONFIG;
	}

	return res;
}
