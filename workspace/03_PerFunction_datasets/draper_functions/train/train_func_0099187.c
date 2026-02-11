__connman_service_set_passphrase(struct connman_service *service,
					const char *passphrase)
{
	int err = 0;

	if (service->immutable == TRUE || service->hidden == TRUE)
		return -EINVAL;

	err = check_passphrase(service, service->security, passphrase);

	if (err == 0) {
		g_free(service->passphrase);
		service->passphrase = g_strdup(passphrase);

		if (service->network != NULL)
			connman_network_set_string(service->network,
							"WiFi.Passphrase",
							service->passphrase);
		service_save(service);
	}

	return err;
}
