pop3_store_get_service_name (CamelNetworkService *service,
                             CamelNetworkSecurityMethod method)
{
	const gchar *service_name;

	switch (method) {
		case CAMEL_NETWORK_SECURITY_METHOD_SSL_ON_ALTERNATE_PORT:
			service_name = "pop3s";
			break;

		default:
			service_name = "pop3";
			break;
	}

	return service_name;
}
