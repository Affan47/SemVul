provision_service_wifi(gpointer key,
				struct connman_config_service *config,
				struct connman_service *service,
				struct connman_network *network,
				const void *ssid, unsigned int ssid_len)
{
	if (config->eap != NULL)
		__connman_service_set_string(service, "EAP", config->eap);

	if (config->identity != NULL)
		__connman_service_set_string(service, "Identity",
							config->identity);

	if (config->ca_cert_file != NULL)
		__connman_service_set_string(service, "CACertFile",
							config->ca_cert_file);

	if (config->client_cert_file != NULL)
		__connman_service_set_string(service, "ClientCertFile",
						config->client_cert_file);

	if (config->private_key_file != NULL)
		__connman_service_set_string(service, "PrivateKeyFile",
						config->private_key_file);

	if (g_strcmp0(config->private_key_passphrase_type, "fsid") == 0 &&
					config->private_key_file != NULL) {
		char *fsid;

		fsid = config_pem_fsid(config->private_key_file);
		if (fsid == NULL)
			return;

		g_free(config->private_key_passphrase);
		config->private_key_passphrase = fsid;
	}

	if (config->private_key_passphrase != NULL) {
		__connman_service_set_string(service, "PrivateKeyPassphrase",
						config->private_key_passphrase);


	}

	if (config->phase2 != NULL)
		__connman_service_set_string(service, "Phase2", config->phase2);

	if (config->passphrase != NULL)
		__connman_service_set_string(service, "Passphrase", config->passphrase);

	if (config->hidden == TRUE)
		__connman_service_set_hidden(service);
}
