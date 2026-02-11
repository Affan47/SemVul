wi_host_addresses(wi_host_t *host) {
	wi_array_t		*addresses;

	if(!host->string) {
		addresses = _wi_host_addresses_for_interface_string(NULL);
	} else {
		addresses = _wi_host_addresses_for_host_string(host->string);

		if(!addresses && wi_error_domain() == WI_ERROR_DOMAIN_GAI)
			addresses = _wi_host_addresses_for_interface_string(host->string);
	}

	return addresses;
}
