_adcli_calc_netbios_name (const char *host_fqdn)
{
	const char *dom;
	char *computer_name;


	dom = strchr (host_fqdn, '.');


	if (dom == host_fqdn) {
		_adcli_err ("Couldn't determine the computer account name from host name: %s",
		            host_fqdn);
		return NULL;

	} else if (dom == NULL) {
		computer_name = strdup (host_fqdn);
		return_val_if_fail (computer_name != NULL, NULL);

	} else {
		computer_name = strndup (host_fqdn, dom - host_fqdn);
		return_val_if_fail (computer_name != NULL, NULL);
	}

	_adcli_str_up (computer_name);
	if (strlen (computer_name) > 15) {
		computer_name[15] = 0;
		_adcli_info ("Truncated computer account name from fqdn: %s", computer_name);
	} else {
		_adcli_info ("Calculated computer account name from fqdn: %s", computer_name);
	}

	return computer_name;
}
